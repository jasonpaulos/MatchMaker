<?php
	require 'date.php';
	
	//If it's not a valid time, redirects to index.php
	//Might want to consider also echoing a link to help browsers which don't respect the redirect
	if(!isValidTime(time())){
		header('Location: index.php');
		die();
	}
	
	require 'mobile.php';
	require 'questions.php';
	echoDoctype();
?>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<link type="text/css" rel="stylesheet" href="styles.css" />
	<title>Register</title>
	<?php
		echoMeta();
	?>
</head>
<body>
	<div class="page">
		<h1 class="title">Match Maker</h1>
		
		<div class="content">
			<h3>To register, please answer the questions below, then click submit</h3>
			
			<form action="submit.php" method="POST">
				<table>
					<tr>
						<td>First Name:</td>
						<?php
							$value = '';
							$help = false;
							
							if(isset($_POST['firstName']) && !isNameValid(($value = $_POST['firstName']), false)){
								$help = true;
								echo '<td style="text-align: center; background-color: red">';
							}else{
								echo '<td style="text-align: center">';
							}
							
							echo '<input type="text" style="width: 90%" name="firstName" maxlength="20" pattern="^[a-zA-Z- ]+$" title="Only letters, hyphens, and spaces" value="'.htmlspecialchars($value).'" required /></td>';
							
							if($help){
								echo '</tr><tr><td colspan="3" style="color: red">Only letters, hyphens, and spaces are accepted</td>';
							}
						?>
					</tr>
					<tr>
						<td>Middle Initial:</td>
						<?php
							$value = '';
							$help = false;
							
							if(isset($_POST['middleName']) && !isNameValid(($value = $_POST['middleName']), true)){
								$help = true;
								echo '<td style="text-align: center; background-color: red">';
							}else{
								echo '<td style="text-align: center">';
							}
							
							echo '<input type="text" style="width: 90%" name="middleName" maxlength="1" pattern="^[a-zA-Z]$" title="Only letters" value="'.htmlspecialchars($value).'" /></td>';
							
							if($help){
								echo '</tr><tr><td colspan="3" style="color: red">Only letters are accepted</td>';
							}
						?>
					</tr>
					<tr>
						<td>Last Name:</td>
						<?php
							$value = '';
							$help = false;
							
							if(isset($_POST['lastName']) && !isNameValid(($value = $_POST['lastName']), false)){
								$help = true;
								echo '<td style="text-align: center; background-color: red">';
							}else{
								echo '<td style="text-align: center">';
							}
							
							echo '<input type="text" style="width: 90%" name="lastName" maxlength="20" pattern="^[a-zA-Z- ]+$" title="Only letters, hyphens, and spaces" value="'.htmlspecialchars($value).'" required /></td>';
							
							if($help){
								echo '</tr><tr><td colspan="3" style="color: red">Only letters, hyphens, and spaces are accepted</td>';
							}
						?>
					</tr>
					
					<tr>
						<td>Gender:</td>
						<?php
							$value = -1;
							
							if(isset($_POST['gender']) && ($value = $_POST['gender']) == -1){
								echo '<td style="background-color: red">';
							}else{
								echo '<td>';
							}
							
							echo
							'<select name="gender" style="width: 100%" required>
								<option value="-1" disabled '.($value == -1 ? 'selected' : '').'>Select</option>
								<option value="0" '.($value == 0 ? 'selected' : '').'>Male</option>
								<option value="1" '.($value == 1 ? 'selected' : '').'>Female</option>
							</select></td>';
						?>
					</tr>
					
					<tr>
						<td>Grade:</td>
						<?php
							$value = -1;
							
							if(isset($_POST['grade']) && ($value = $_POST['grade']) == -1){
								echo '<td style="background-color: red">';
							}else{
								echo '<td>';
							}
							
							echo
							'<select name="grade" style="width: 100%" required>
								<option value="-1" disabled '.($value == -1 ? 'selected' : '').'>Select</option>
								<option value="0" '.($value == 0 ? 'selected' : '').'>Freshman</option>
								<option value="1" '.($value == 1 ? 'selected' : '').'>Sophomore</option>
								<option value="2" '.($value == 2 ? 'selected' : '').'>Junior</option>
								<option value="3" '.($value == 3 ? 'selected' : '').'>Senior</option>
							</select></td>';
						?>
					</tr>
				</table>
				
				<table style="width: 100%">
					<?php
						echo '<tr><td colspan="5"><hr /></td></tr>';
						
						for($q = 0; $q < count($questions); ++$q){
							$question = $questions[$q];
							$value = -1;
							
							if(isset($_POST[$q]) && ($value = $_POST[$q]) == -1){
								echo '<tr style="background-color: red">';
							}else{
								echo '<tr>';
							}
							
							echo '<td colspan="5" class="question"> '.($q + 1).'. '.$question->text.'</td></tr><tr>';
							
							for($a = 1; $a <= 5; ++$a){
								echo '<td class="answer"><input type="radio" name="'.$q.'" value="'.$a.'" id="'.$q.':'.$a.'" '.($value == $a ? 'checked' : '').' required /><br /><label for="'.$q.':'.$a.'">'.$a.'</label></td>';
							}
							
							echo'</tr><tr>';
							
							for($a = 1; $a <= 5; ++$a){
								$caption = '';
								
								if($a == 1){
									$caption .= '<label for="'.$q.':'.$a.'">'.$question->disagree.'</label>';
								}elseif($a == 5){
									$caption .= '<label for="'.$q.':'.$a.'">'.$question->agree.'</label>';
								}
								
								echo '<td class="answer">'.$caption.'</td>';
							}
							
							echo '</tr><tr><td colspan="5"><hr /></td></tr>';
						}
					?>
				</table>
				
				<input type="submit" value="Submit" style="width: 250px"/>
			</form>
		</div>
	</div>
</body>
</html>
