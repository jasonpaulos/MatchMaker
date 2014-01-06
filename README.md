# MatchMaker

## What is it?

Every February, Sandra Day O'Connor High School hosts a matchmaking event where students can fill out a survey and then receive a list of top matches in the school based off their answers to the survey a few weeks later. This year (2014), we have decided to stop outsourcing the matching process and to use a combination of an online survey and a computer matching program instead. The MatchMaker project is the implementation of these features and has been in development for months leading up to this year's event. Every snippet of code has been custom made to work toward the goal of having a completely in-house, efficient, and extendible tool that is easy to use and works well. The MatchMaker project is licensed under the MIT license, and I encourage you to take advantage of this by examining the code, modifying it, and even extending the application to fit your own purposes. For more information, please see LICENSE.

## How does it work?

There are two main parts to the project: the online survey and the matching program. The online survey, which can be found in the folder Website, is a collection of PHP files that work together in order to provide questions to students and to store their answers in a database. For more information, please see Website/DOCUMENTATION.md. The matching program, which is the real meat and potatoes of this project, is a Qt GUI application written in C++ that takes a database as an input (possibly one created by the online survey), performs matching operations on the data, and then outputs the matches to a PDF file. The application's source code can be found in the folder Qt_MatchMaker. For more information, please see Qt_MatchMaker/DOCUMENTATION.md.

## How can I use it?

The current release builds of the MatchMaker application for Windows (32 and 64 bit) and for Mac OSX (x86_64) can be found on the GitHub project page: https://github.com/JasonPaulos/MatchMaker. If you want to build the application from source code, please see Qt_MatchMaker/BUILDING.md.

## Who created it?

Jason Paulos, a sophomore as of now, created the matching program and the PHP features of the online survey. Cole Green, also a sophomore, created the HTML layout of the online survey. Matthew Dobosz, a sophomore as well, created the application icons.
