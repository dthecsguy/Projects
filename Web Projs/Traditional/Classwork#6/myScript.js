$(document).ready(function(){
	var calculateTax = {getStateTax: "", getFedTax: ""};
	var employee = {stateTax: 0, fedTax: 0};
	var radios;
	var taxClick = false;
	
	$("#output").hide();
	
	calculateTax.getStateTax = function(num){
		return num * 0.08;
	}
	
	calculateTax.getFedTax = function(num){
		return ((num >= 10000) ? (num * 0.2) : (num * 0.1));
	}
	
	function readForm(){
		employee.nameFirst = $("#nameFirst").val();
		employee.nameLast = $("#nameLast").val();
		employee.salary = $("#salary").val();
		employee.age = $("#ageN").val();
		employee.manager = $("#manager").prop("checked");
		employee.comments = $("#comments").val();
		
		if($("#genderM").prop("checked"))
		{
			employee.gender = "Male";
		}
		else if($("#genderF").prop("checked"))
		{
			employee.gender = "Female";
		}
		else
		{
			employee.gender = "Other";
		}
		
		if(employee.manager)
		{
			employee.stateTax = 0;
			employee.fedTax = 0;
		}
		else if(!taxClick){		
			employee.stateTax = getStateTax(salary);
			employee.fedTax = getFedTax(salary);
		}
		else if(taxClick){
			employee.stateTax = $("#sTaxVal").val();
			employee.fedTax = $("#fTaxVal").val();
		}

		$("#empForm")[0].reset();
		$("#empForm").hide();
	}

	function writeForm(){
		$("#empInfo").html(employee.nameFirst + " " + employee.nameLast + ": <br/>" +
							"Salary: " + employee.salary + "<br/>" + 
							"Age: " + employee.age + "<br/>" +
							"Gender: " + employee.gender + "<br/>" +
							"Manager: " + employee.manager + "<br/>" +
							"State Tax: " + employee.stateTax + "<br/>" +
							"Federal Tax: " + employee.fedTax + "<br/>" + 
							"<u>Employee Comments</u><br/>&emsp;" + employee.comments);
							
		$("#output").show();
	}
	
	$("#taxes").click(function (){
		taxClick = true;
		if($("#salary").val() == 0.01){
			window.alert("Invalid Salary Amount");
		}
		else{
			employee.stateTax = calculateTax.getStateTax($("#salary").val());
			employee.fedTax = calculateTax.getFedTax($("#salary").val());
		}
		
		$("#sTaxVal").val(employee.stateTax);
		$("#fTaxVal").val(employee.fedTax);
	});
	
	$("#submit").click(function(){
		readForm();
		writeForm();
	});
});