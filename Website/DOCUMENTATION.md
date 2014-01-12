#The MatchMaker Website

This folder contains the files necessary to run the online survey part of the MatchMaker project. Here you will find a brief documentation of the purpose of each of the files in this folder. For more information about a file, please refer to the actual file.

* __database.php__ - This file is responsible for the creation of the database used to store user information. You can change what database is used as well as which table will be used here.

* __data.php__ - This file manages the timezone as well as the start and end dates of registration.

* __questions.php__ - This file contains an array of every question as well as a function to verify that the name fields are properly formatted. Here you can add questions to the $questions array by using createQuestion(...).

* __mobile.php__ - This file contains special routines for displaying the website to mobile browsers.

* __index.php__ - This is the homepage of the website. Here, depending on whether or not registration is open, a link to the registration page is displayed. In addition to that, you may want to add a description and more information to this page.

* __register.php__ - This file contains all of the questions for registration. It can accept POST data because submit.php will resend the data to this page if some information is missing or is not formatted correctly. This is useful because the user will not have to redo the entire survey if they accidentally forget to answer one question (and their browser ignores the required fields).

* __submit.php__ - This file receives the information sent from register.php. If some of it is missing, incorrectly formatted, or someone has already registered with the sent name, it will send the POST back to register.php using input tags with the type "hidden". If everything is correct, it will insert the information into the database.

* __view.php__ - This file displays all of the data that is currently in the database. It is for testing purposes only and should not be placed in a public website.

* __styles.css__ - Here is where the layout of the website is created. Any changes here will be applied to every viewable page.
