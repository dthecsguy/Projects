$(document).ready(function(){
	var pass = "thepassword";
	var email = "demarcussales10@gmail.com";
	var file;
	var uEmail;
	var uPass;

	function getInfo(){
		uEmail = $("#emailInput").val();
		uPass = $("#passInput").val();
		file = $("#fileInput").val();
	}
	
	function checkInfo(){
		if(pass == uPass && email == uEmail)
		{
			$("#display").append("Your email was: " + email + "<br/>");
			$("#display").append("Your password was: " + pass + "<br/>");
			$("#display").append("Your file was: " + file + "<br/>");
			$("#theForm")[0].reset();
		}
		else{
			alert("Information was not correct!!");
			$("#theForm")[0].reset();
		}
	}
	
	$("#Test").click(function(){
		getInfo();
		checkInfo();
	});
	
	
});