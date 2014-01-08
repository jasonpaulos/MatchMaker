<?php
	require 'date.php';
	
	//If it's not a valid time, redirects to index.php
	//Might want to consider also echoing a link to help browsers which don't respect the redirect
	if(!isValidTime(time())){
		header('Location: index.php');
		die();
	}
	
	require 'mobile.php';
	echoDoctype();
?>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<link type="text/css" rel="stylesheet" href="styles.css" />
	<title>Submit</title>
	<?php
		echoMeta();
	?>
</head>
<body>
	<div class="page">
		<h1 class="title">Match Maker</h1>
		
		<div class="content">
			<?php				
				require 'database.php';
				
				//This makes sure all of the post data is acceptable
				$valid = 
					isset($_POST['firstName']) &&
					isset($_POST['middleName']) &&
					isset($_POST['lastName']) &&
					isset($_POST['gender']) &&
					isset($_POST['grade']) &&
					($_POST['gender'] == 0 || $_POST['gender'] == 1) &&
					($_POST['grade'] == 0 || $_POST['grade'] == 1 || $_POST['grade'] == 2 || $_POST['grade'] == 3) &&
					isNameValid($_POST['firstName'], false) &&
					isNameValid($_POST['middleName'], true) &&
					isNameValid($_POST['lastName'], false);
				
				for($q = 0; $q < count($questions); ++$q){
					if(!isset($_POST[$q]) && $_POST[$q] > 0 && $_POST[$q] <= 5){
						$valid = false;
					}
				}
				
				$dupe = false;
				
				if($valid){
					$names = array(
						':firstName' => ucwords(strtolower(htmlspecialchars($_POST['firstName']))),
						':middleName' => strtoupper(htmlspecialchars($_POST['middleName'])),
						':lastName' => ucwords(strtolower(htmlspecialchars($_POST['lastName']))),
					);
					
					$select = $db->prepare('SELECT gender FROM '.$table.' WHERE
						firstName=:firstName AND
						middleName=:middleName AND
						lastName=:lastName');
					$select->execute($names);
					
					$dupe = $select->rowCount() > 0;
					if($dupe){
						$valid = false;
					}
				}
								
				if(!$valid){
					if($dupe){
						echo '<h2>The user '.$names[':firstName'].(empty($names[':middleName']) ? ' ' : ' '.$names[':middleName'].' ').$names[':lastName'].' has already registered.</h2>';
					}else{
						echo '<h2>Some of your answers were not formatted correctly. Please go back and correct any questions that are highlighted.</h2>';
					}
					
					echo '<form action="register.php" method="POST">';
					
					if(isset($_POST['firstName'])){
						echo '<input type="hidden" name="firstName" value="'.htmlspecialchars($_POST['firstName']).'" />';
					}
					if(isset($_POST['middleName'])){
						echo '<input type="hidden" name="middleName" value="'.htmlspecialchars($_POST['middleName']).'" />';
					}
					
					if(isset($_POST['lastName'])){
						echo '<input type="hidden" name="lastName" value="'.htmlspecialchars($_POST['lastName']).'" />';
					}
					
					echo '<input type="hidden" name="gender" value="'.(isset($_POST['gender']) ? htmlspecialchars($_POST['gender']) : '-1').'" />';
					
					echo '<input type="hidden" name="grade" value="'.(isset($_POST['grade']) ? htmlspecialchars($_POST['grade']) : '-1').'" />';
					
					for($q = 0; $q < count($questions); ++$q){
						echo '<input type="hidden" name="'.$q.'" value="'.(isset($_POST[$q]) ? htmlspecialchars($_POST[$q]) : '-1').'" />';
					}
					
					echo '<input type="submit" value="Back" style="width: 250px">';
					
					echo '</form>';
				}else{
					$insert = 'INSERT INTO '.$table.' (firstName, middleName, lastName, gender, grade';
					$values = 'VALUES (:firstName, :middleName, :lastName, :gender, :grade';
					$array = array(
						':firstName' => $names[':firstName'],
						':middleName' => $names[':middleName'],
						':lastName' => $names[':lastName'],
						':gender' => htmlspecialchars($_POST['gender']),
						':grade' => htmlspecialchars($_POST['grade']),
					);
					for($q = 0; $q < count($questions); ++$q){
						$insert .= ', q'.$q;
						$values .= ', :q'.$q;
						$array[':q'.$q] = htmlspecialchars($_POST[$q]);
					}
					$insert .= ') ';
					$values .= ')';
										
					$input = $db->prepare($insert.$values);
					$input->execute($array);
					
					echo '<h2>Thank you for registering. Your answers have been saved and you can safely close this page.</h2>';
				}
			?>
		</div>
	</div>
</body>
</html>