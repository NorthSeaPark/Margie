//= require Frameworks/progressbar_framework
Bart_Framework = function() {
	var task = this;

	/* ==== the following three chunks are set up upon task = new Bart_Framework(); === */

	// default variables
	task.trialCounter = 0;
	task.pumps = 0;
    task.balloonImageArray = [];
    task.scaleImageArray = [];
	task.MAX_PRACTICE_TRIALS = 100;
	task.MAX_TRIALS = 200;
	task.MAX_PUMPS = 1000;

	// task specific variables (may be overwritten - these are defaults)
	task.USE_MONEY = true; // false means use points
	task.STARTING_SCORE = 0.05;
	task.SCORE_ITERATOR = 0.05;
	task.SCOREBAR_MAX = null;

	/*
	 * task.init is the first function called
   * this sets up background, initial score, and container navigation
   */
	task.init = function() {
        console.log('Initializing Bart')
		initOnWindowUnload();
        task.loadAssets();

        $("html").css({"background": "#B2D1F7"});


		task.currentScore = task.STARTING_SCORE;
		task.totalScore = 0;
		task.updateCurrentScore();
		task.updateTotalScore();

		// set up scorebar if a scorebar max is set
		if (task.SCOREBAR_MAX) {
			var pos_scorebar_container = document.getElementById("pos-scorebar-container").style.width = "100%";
		}

		// main container, after practice break container, and finished containers are hidden
        $("#container").hide();
        $("#finished-container").hide();

        $(".toggle-instructions-btn").on("click", function() {
            $(".instructions-content").toggle();
            $(this).text(function(i, text){
                return text === "Show Instructions" ? "Hide Instructions" : "Show Instructions";
            });
        });

		// when start button is pressed, instructions are hidden
		// main container is shown and task is started
        InstructionsController.init({
            "0": {
                next: function() {
                    $(".instructions-container").hide();
                    $("#container").show();

                    StartTask(participant.incompletePath, participant.finishPath);
                    $("#balloon-container").hide();
                    $("#buttons-container").hide();
                    // calls engine to set up practice trial numbers
                    $.ajax({
                        url: participant.requestPath,
                        context: task,
                        data: {trialNumber: -1, nPumps: -1, outcome: -1, timeArray: 0},
                        success: function(data) {
                            task.MAX_PRACTICE_TRIALS = parseInt(data[0]);
                            task.MAX_TRIALS = parseInt(data[1]);
                            task.getProbability(task.trialCounter, 0, 0, 0);
                            task.pumps = 0;
                        }
                    });
                    task.setupEventListeners();
                }
            },
            final: function(){
                task.reset(task.trialCounter, task.pumps, task._outcome, task.timeArray);
                task.currentScore = task.STARTING_SCORE;
                task.updateCurrentScore();
            },
            "warning-container": "instructions-warning"
        });
    };

	/*
	 * task.loadAssets is called from task.init
   * this adds all the needed images to the balloonImageArray & scaleImageArray and loads audio files
   */
	task.loadAssets = function() {
		// initialize audio files
		task.popAudio = new Audio("<%= audio_url("#{AppConfig.ASSET_MAP['bart']}/pop.mp3") %>");
		task.pumpAudio = new Audio("<%= audio_url("#{AppConfig.ASSET_MAP['bart']}/pump.mp3") %>");
		task.collectAudio = new Audio("<%= audio_url("#{AppConfig.ASSET_MAP['bart']}/slot.mp3") %>");

  	var colors = ["blue", "cyan", "green", "yellow", "orange", "red"];
  	task.balloonImageArray[0] = new Image();
  	task.balloonImageArray[0].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/blue.png") %>";

  	task.balloonImageArray[1] = new Image();
  	task.balloonImageArray[1].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/cyan.png") %>";

  	task.balloonImageArray[2] = new Image();
  	task.balloonImageArray[2].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/green.png") %>";

  	task.balloonImageArray[3] = new Image();
  	task.balloonImageArray[3].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/yellow.png") %>";

  	task.balloonImageArray[4] = new Image();
  	task.balloonImageArray[4].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/orange.png") %>";

  	task.balloonImageArray[5] = new Image();
  	task.balloonImageArray[5].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/red.png") %>";

  	task.balloonImageArray[6] = new Image();
  	task.balloonImageArray[6].src = "<%= image_url("#{AppConfig.ASSET_MAP['bart']}/balloons/pink.png") %>";

  	<% (0..20).each do |i| %>
    	task.scaleImageArray[<%= i %>] = new Image();
    	task.scaleImageArray[<%= i %>].src = '<%= image_url("#{AppConfig.ASSET_MAP['bart']}/scales/#{i * 5}.png") %>';
  	<% end %>
	}

	/*
   * task.updateScorebar is called from updateTotalScore() and newTrial()
   * The score bar is updated using the task.totalScore variable
   */
	task.updateScorebar = function() {
		var pos_scorebar = document.getElementById("pos-scorebar");
        var ratio;
        if(task.trialCounter < task.MAX_PRACTICE_TRIALS){
            ratio = task.trialCounter / task.MAX_PRACTICE_TRIALS;
        } else {
            ratio = (task.trialCounter - task.MAX_PRACTICE_TRIALS)/task.MAX_TRIALS;
        }
		pos_scorebar.style.width = ratio*100 + '%';
		pos_scorebar.style.backgroundColor = 'green';
	}

	/*
	 * task.getProbability is called from task.init and task.reset
   * calculates probability to be used in next trial
   */
	task.getProbability = function(trialNumber, nPumps, outcome, timeArray) {
		timeArray = task.formatTimes(timeArray).toString();

  	$.ajax({
    	url: participant.requestPath,
   	 	context: task,
    	data: {trialNumber: trialNumber, nPumps: nPumps, outcome: outcome, timeArray: timeArray},
    	success: function(data) {
      	if (trialNumber == task.MAX_TRIALS + task.MAX_PRACTICE_TRIALS) {
       	 EndTask("#container");
      	} else {
       	 task.probability = parseFloat(data[0]);
       	 task.MAX_PUMPS = parseInt(data[1]);
       	 task.setupBalloon();
      	}
    	}
 	 });
	}

	/*
	 * task.formatTimes is called from task.getProbability
   * format time it took between consecutive button clicks (pump or collect)
   */
	task.formatTimes = function(timeArray) {
  	calculated = [(timeArray[1]-timeArray[0])]
  	for (var i = 2; i < timeArray.length; i++) {
    	calculated.push(timeArray[i]-timeArray[i-1]);
  	}
  	return calculated;
	}

	/*
	 * task.setupBalloon is called from task.getProbability
   * uses new calculated probability to set up new trial
   */
	task.setupBalloon = function() {
  	// scaleIndex calculates index of image in array based on probability
  	// the -1 is due to indexing at zero
  	var balloonIndex;
  	var scaleIndex = Math.round(((task.probability * 100) / 5));

  	if (task.probability < 0) {
    	balloonIndex = 6; // pink
    	$("#current-score").css("color", "black");
  	} else if (task.probability < 0.25) {
   	 balloonIndex = 0; // blue
    	$("#current-score").css("color", "white");
  	} else if (task.probability < 0.4) {
   	 balloonIndex = 1; // cyan
   	 $("#current-score").css("color", "black");
  	} else if (task.probability < 0.65) {
   	 balloonIndex = 2; // green
   	 $("#current-score").css("color", "black");
 	 } else if (task.probability < 0.75) {
   	 balloonIndex = 3; // yellow
   	 $("#current-score").css("color", "black");
 	 } else if (task.probability < 0.85) {
   	 balloonIndex = 4; // orange
  	  $("#current-score").css("color", "black");
  	} else {
  	  balloonIndex = 5; // red
   	 $("#current-score").css("color", "white");
  	}

  	$("#balloon-image").attr("src", task.balloonImageArray[balloonIndex].src);
  	if(scaleIndex >= 0) {
   	 $("#scale-image").attr("src", task.scaleImageArray[scaleIndex].src);
 	 } else {
 	   $("#scale-image").attr("src", task.scaleImageArray[0].src);
 	 }

  	$("#balloon-container").show();
  	$("#buttons-container").show();
 	 	$("#current-score").show();

  	task.timeArray = [Date.now()];
	}

	/*
	 * task.setupEventListeners is called from task.init
   * creates actions for button clicks
   */
	task.setupEventListeners = function() {
  	$("#pump-button").click(function() {
    	task.timeArray.push(Date.now());
    	task.handlePump();
  	});

  	$("#collect-button").click(function() {
    	task.timeArray.push(Date.now());
    	task.handleCollect();
 	 });
	}

	/* ===== At this point the program waits for the user to press a button ===== */

	/*
	 * task.handlePump runs when the pump button is clicked
   * Decides if balloon gets pumped or is popped
   */
	task.handlePump = function() {
  	$("#pump-button").css("border", "1px solid black");
  	window.setTimeout(function() {
   	 $("#pump-button").css("border", "1px solid #B2D6F7");
  	}, 300);

  	var p = task.pump();
		task.currentScore = (task.pumps + 1) * task.SCORE_ITERATOR;

  	if (p == 1) {
			// clear balloon
			$("#pump-button").off();
			$("#collect-button").off();
			$("#balloon-image").attr("src", '<%= image_url("#{AppConfig.ASSET_MAP['bart']}/popped.png") %>');
			$("#current-score").hide();
			$("#buttons-container").hide();

			task.popAudio.play();
			task.nextTrial(1);
			task.currentScore = task.STARTING_SCORE;
  	} else {
  	  task.pumpAudio.play();
  	}

		task.updateCurrentScore();
	}

	/*
	 * task.pump is called from task.handlePump
   * returns 1 if pumps = max_pumps
   */
	task.pump = function() {
  	task.pumps++;
  	if (task.pumps == task.MAX_PUMPS) {
    	return 1;
  	}
  	return 0;
	}

	/*
	 * task.handleCollect runs when the collect button is clicked
   * money/points are transfered to piggy bank
   */
	task.handleCollect = function() {
 	 $("#pump-button").off();
 	 $("#collect-button").off();
 	 $("#buttons-container").hide();

  	/* increment trial counter */
	 	task.currentScore = (task.pumps+1) * task.SCORE_ITERATOR;
		var iter = task.pumps+1;

  	var timesAudioPlayed = 1; /* it will be after event listener*/
  	task.collectAudio.addEventListener("ended", function() {
   	 if (timesAudioPlayed >= 2) {
    	  task.collectAudio.removeEventListener("ended", task);
    	  return;
    	}

   	 task.collectAudio.currentTime = 0;
   	 task.collectAudio.play();
   	 timesAudioPlayed++;
  	});

  	task.collectAudio.play();

  	var collectInterval = setInterval(function() {
	    task.totalScore += task.SCORE_ITERATOR;
 	   	task.currentScore -= task.SCORE_ITERATOR;
    	task.updateCurrentScore();
    	task.updateTotalScore();
    	iter--;

    	if (!iter) {
     	 clearInterval(collectInterval);
      	task.nextTrial(0);
    	}
  	}, 1500/iter);


	}

	/*
	 * task.updateCurrentScore is called from handlePump & handleCollect
   * current score is updated on view
   */
	task.updateCurrentScore = function() {
		if (task.currentScore == -0) task.currentScore = 0;
		p = task.probability;
		if ((p < 0.25 && p > 0) || p >= .85) {
			$("#current-score").css("color", "black");
    	setTimeout(function() {
     		$("#current-score").css("color", "white");
				if (task.USE_MONEY) {
     	 		$("#current-score").text("$" + task.currentScore.toFixed(2));
				} else {
					$("#current-score").text(task.currentScore);
				}
   	 	}, 100);
 	 	} else {
  	  $("#current-score").css("color", "white");
  	  setTimeout(function() {
   	  	$("#current-score").css("color", "black");
				if (task.USE_MONEY) {
   	   		$("#current-score").text("$" + task.currentScore.toFixed(2));
				} else {
					$("#current-score").text(task.currentScore);
				}
   	 	}, 100);
  	}
	}

	/*
	 * task.updateTotalScore is called from handleCollect
   * total score is updated on view
   */
	task.updateTotalScore = function() {
		$("#total-score").css("color", "#ff6700");
  	setTimeout(function() {
    	$("#total-score").css("color", "white");
   		if (task.totalScore == -0) task.totalScore = 0;
			if (task.USE_MONEY) {
    		$("#total-score").text("$" + task.totalScore.toFixed(2));
			} else {
				$("#total-score").text(task.totalScore);
			}
 	 	}, 100);

	}

	/*
	 * task.nextTrial is called from handlePump (outcome = 1) & handleCollect (outcome = 0)
   * shows pause block if practice trials are over, otherwise sets up next trial
   */
	task.nextTrial = function(outcome) {
  	task.trialCounter++;

  	setTimeout(function() {
   	 $("#balloon-container").hide();
    	if (task.trialCounter == task.MAX_PRACTICE_TRIALS) {
				task.totalScore = 0;
				task.updateTotalScore();
            task._outcome = outcome; //so it's accessible in IC
            InstructionsController.showCurrent();
    	} else {
    	  task.reset(task.trialCounter, task.pumps, outcome, task.timeArray);
     	  task.currentScore = task.STARTING_SCORE;
    	  task.updateCurrentScore();
   	 }

  	}, 750);
        if (task.SCOREBAR_MAX) {
           task.updateScorebar();
        }
	}

	/*
	 * task.reset is called from task.nextTrial
   * the probability for the next trial is calculated and pumps is reset
   */
	task.reset = function(trialCounter, pumps, outcome, timeArray) {
  	task.getProbability(trialCounter, pumps, outcome, timeArray);
  	task.pumps = 0;
		task.setupEventListeners();
	}



}