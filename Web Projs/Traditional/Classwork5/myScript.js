$(document).ready(function(){
	var title, email, areaText;
	
	function getInfo(){
		title = $("#title").val();
		email = $("#email").val();
		areaText = $("#textses").val();
	}
	
	function holdInfo(){
		$("#hold").append("<h1>" + title + ": " + "</h1>");
		$("#hold").append("<h4><p>" + areaText + "</p></h4>");
		$("#hold").append("<small><p>" + email + "</p></small>");
	}
	
	$("#submit").click(function(){
		getInfo();
		$("#myForm")[0].reset();
		$("#myForm").hide();
		holdInfo();
	});
});