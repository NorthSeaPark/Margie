var BartCM = {
	Start: function() {
		console.log("Starting BartCM task");
		task = new Bart_Framework();
		task.USE_MONEY = false;
		task.STARTING_SCORE = 5;
		task.SCORE_ITERATOR = 5;
		task.SCOREBAR_MAX = 250*5;
		task.init();
	}
}