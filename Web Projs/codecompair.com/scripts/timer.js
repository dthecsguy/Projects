function displayTimer() {
	var initial = new Date();
	var Final = new Date();
	Final.setTime(initial.getTime() + 300000);
	
	var interval = setInterval( changeTimer(Final), 1000);
	
	while(true){
		if(Final.getSeconds() - Date.getSeconds() <= 0) {
			clearInterval(interval);
		}
	}
}

function changeTimer(Final){
	var now = new Date();
	let current = new Date();
	current.setTime(Final.getTime() - now.getTime());
	$('#timer').text = current.getMinutes() + ":" + current.getSeconds();
}
displayTimer();