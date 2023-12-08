/*-------------------------------------------
// Course: COMP 150
// Last Name: Singh
// First Name: Rajveer
// Student ID: 300202522
// 
// File: Project02sportFall23_SinghRS.cpp

// Summary: Simulates the events of a basketball World Cup competition
			involving 4 teams. Uses randomization to decide what actions
			occur in a game. It also has a fun superhero theme 
			 
*-------------------------------------------*/
#include<iostream>
#include<string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include<fstream>
using namespace std;



// Global Constants
const int NUM_PLAYERS = 4;
const int NUM_STATS = 6;
const int NUM_TEAMS = 4;


// Structures
struct foul {
	string foul_type[4] = {"Personal Foul", "Offensive Foul", "Shooting Foul", "Technical Foul"};
	int num;
	int guilty_player;
	int innocent_player;
};
struct ability {
	string attack01_name = "attack 1";
	string attack02_name = "attack 2";
	string defend01_name = "defense 1";
	string defend02_name = "defense 2";
	int attack01_val;
	int attack02_val;
	int defend01_val;
	int defend02_val;
};
struct player {
	string name;
	ability abilities;
	double weight_magnitude; 
	double performance;
	int teamwork; 
	int endurance; 
	int foul_tendency;
	int speed; 
	int aim_accuracy; 
	int agility; 
};
struct team {
	string name;
	int skill_level;
	int games_played = 0;
	player players[NUM_PLAYERS];
	bool hasBall = false;
	int goals = 0;
	int total_goals = 0;
	int wins;
	double performance;
} justice_league_team, avengers_team, teen_titans_team, x_men_team;

struct game {
	int mode;
	string winner;
} main_game;


// Global variables
team teams[NUM_TEAMS] = {justice_league_team, avengers_team, teen_titans_team, x_men_team}; // Storing on the teams in a single array

string hoop =
						   "            X[3]           \n"	
						   "				           \n"	
						   "                     X[2]  \n"	
						   "    X[1]				   \n"
			   			   " __________________________\n"
                    	   "|__________________________|\n"
                           " \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n"
                           "  \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n"
                           "   \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n"
                           "    \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n"
                           "     |/\\/\\/\\/\\/\\/\\/\\/\\|\n"
                           "      |/\\/\\/\\/\\/\\/\\/\\|\n"
                           "      |\\/\\/\\/\\/\\/\\/\\/|\n"
                           "      |/\\/\\/\\/\\/\\/\\\\/|\n";
			

// Function prototypes
int automaticStat(int& stat);
void teamStats(int team_num);
void dribble();
void jumpBall(int team_one, int team_two, int& starting_player);
void scoring(int team_one, int team_two, int& starting_player);
void interception(int team_one, int team_two, int& starting_player);
void fouls(int team_one, int team_two, int& starting_player, string hoop);
void overtime(int team_one, int team_two);
void playGame(int team_one, int team_two, ofstream& outputfile);
void displayRoundResults(int team_one, int team_two);
void sortArrayPerformance(team array[], int array_size);
void displayResults(int team_one, int team_two, ofstream& outputfile);
int miniGame(int location, int shot, int answer);
void inputError(int &input, int x, int y);


int main()
{	
	// Seeding the random function
	srand(time(0));
	
	// Loading output file
	ofstream outputfile;
	outputfile.open("gameResult.txt");
	
	// Storing graphics and basic player information
	string game_title, basketball_pic;
	int stat_mode;
	
	game_title = " _               _        _   _           _ _\n" 
				 "| |__   __ _ ___| | _____| |_| |__   __ _| | |\n"
 				 "| '_ \\ / _` / __| |/ / _ \\ __| '_ \\ / _` | | |\n"
 				 "| |_) | (_| \\__ \\   <  __/ |_| |_) | (_| | | |\n"
 				 "|_.__/ \\__,_|___/_|\\_\\___|\\__|_.__/ \\__,_|_|_|";
	
	basketball_pic ="             ..ee$$$$$ee..\n"
					"         .e$*\"\"    $    \"\"*$e.       [WORLD CUP]\n"
					"       z$\"*.       $         $$c\n"
					"    z$\"   *.      $       .P  ^$c\n"
					"   d\"      *      $      z\"     \"b\n"
					"  $\"        b     $     4%       ^$\n"
					" d%         *     $     P         '$\n"
					".$          'F    $    J\"          $r\n"
					"4L...........b....$....$...........J$\n"
					"$F           F    $    $           4$\n"
					"4F          4F    $    4r          4P\n"
					"^$          $     $     b          $%\n"
					" 3L        .F     $     'r        JP\n"
					"  *c       $      $      3.      z$\n"
					"   *b     J\"      $       3r    dP\n"
					"    ^$c  z%       $        \"c z$\"\n"
					"      \"*$L        $        .d$\"\n"
					"         \"*$ee..  $  ..ze$P\"\n"
					"             \"\"*******\"\"\n";
	
	string hoop1 = "                    X[3]         \n"
					   "                           X[1] \n"
					   "              X[2]              \n"
		 			   "            ____________________\n"   
					   "           |____________________|                            ____|\n"  
 					   "            \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/                            \\%/ |~~\\\n"       
  					   "             \\/\\/\\/\\/\\/\\/\\/\\/\\/               o                |\n"       
   					   "              \\/\\/\\/\\/\\/\\/\\/\\/             o//                 |\n"          
                       "               \\/\\/\\/\\/\\/\\/\\/              8                   |\n"      
                       "                |/\\/\\/\\/\\/\\|              / >               ~~~~~~\n"           
                       "                |\\/\\/\\/\\/\\/|         __________________________________\n"          
                       "                |/\\/\\/\\/\\/\\|";
					   	   
	string hoop2 = "                    X[3]         \n"
					   "                           X[1] \n"
					   "              X[2]              \n"
		 			   "            ____________________\n"   
					   "           |____________________|                                     ____|\n"  
 					   "            \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/                                     \\%/ |~~\\\n"       
  					   "             \\/\\/\\/\\/\\/\\/\\/\\/\\/               o                         |\n"       
   					   "              \\/\\/\\/\\/\\/\\/\\/\\/             o//                          |\n"          
                       "               \\/\\/\\/\\/\\/\\/\\/              8                            |\n"      
                       "                |/\\/\\/\\/\\/\\|              / >                       ~~~~~~\n"           
                       "                |\\/\\/\\/\\/\\/|         __________________________________________________\n"          
                       "                |/\\/\\/\\/\\/\\|";
					   
	string hoop3 = "                    X[3]         \n"                 
					   "                           X[1] \n"
					   "              X[2]              \n"
		 			   "            ____________________\n"   
					   "           |____________________|                                                     ____|\n"  
 					   "            \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/                                                     \\%/ |~~\\\n"       
  					   "             \\/\\/\\/\\/\\/\\/\\/\\/\\/               o                                         |\n"       
   					   "              \\/\\/\\/\\/\\/\\/\\/\\/             o//                                          |\n"          
                       "               \\/\\/\\/\\/\\/\\/\\/              8                                            |\n"      
                       "                |/\\/\\/\\/\\/\\|              / >                                       ~~~~~~\n"           
                       "                |\\/\\/\\/\\/\\/|         __________________________________________________________________\n"          
                       "                |/\\/\\/\\/\\/\\|";        
	
	string court_art =  "                                                             ____|\n"
        					"                                                             \\%/ |~~\\\n"
  							"                                                                 |\n"
  							"                                                                 |\n"
 							"                                                                 |\n"
							"  [1-Deep]	        [2-Middle]	       [3-Close]      ~~~~~~\n"
							"______________________________________________________________________\n";
		
	string court_art1 = "                   ____|\n"
        					"                   \\%/ |~~\\\n"
  							"         o             |\n"
  							"   o//                 |\n"
 							"   8                   |\n"
							"  / >               ~~~~~~\n"
							"______________________________\n";
							
	string hoops[3] = {hoop3, hoop2, hoop1};					
				
	
	// Storing team names
	teams[0].name = "Justice League";
	teams[1].name = "Avengers";
	teams[2].name = "Teen Titans";
	teams[3].name = "X-Men";
	// Storing team justice league player and ability names
	teams[0].players[0].name = "Batman";
	teams[0].players[0].abilities.attack01_name = "Batarang Strike";
	teams[0].players[0].abilities.attack02_name = "Batarang Strike";
	teams[0].players[0].abilities.defend01_name = "Bat Defense Mode";
	teams[0].players[0].abilities.defend02_name = "Tactical Evasion";
	teams[0].players[1].name = "Superman";
	teams[0].players[1].abilities.attack01_name = "Heat Vision Burst";
	teams[0].players[1].abilities.attack02_name = "Sonic Boom";
	teams[0].players[1].abilities.defend01_name = "Fortress Shield";
	teams[0].players[1].abilities.defend02_name = "Invulnerable Stance"; 
	teams[0].players[2].name = "Wonder Woman";
	teams[0].players[2].abilities.attack01_name = "Lasso Strike";
	teams[0].players[2].abilities.attack02_name = "Amazonian Fury";
	teams[0].players[2].abilities.defend01_name = "Bracelet Block";
	teams[0].players[2].abilities.defend02_name = "Divine Shield"; 
	teams[0].players[3].name = "Flash";
	teams[0].players[3].abilities.attack01_name = "Speed Blitz";
	teams[0].players[3].abilities.attack02_name = "Lightning Strike";
	teams[0].players[3].abilities.defend01_name = "Speed Guard";
	teams[0].players[3].abilities.defend02_name = "Time Phasing";
	
	// Storing team avengers player and ability names
	teams[1].players[0].name = "Iron Man";
	teams[1].players[0].abilities.attack01_name = "Repulsor Blast";
	teams[1].players[0].abilities.attack02_name = "Unibeam Assault";
	teams[1].players[0].abilities.defend01_name = "Energy Shield";
	teams[1].players[0].abilities.defend02_name = "Nanotech Armor";
	teams[1].players[1].name = "Captain America";
	teams[1].players[1].abilities.attack01_name = "Shield Bash";
	teams[1].players[1].abilities.attack02_name = "Patriot Strike";
	teams[1].players[1].abilities.defend01_name = "Shield Defense";
	teams[1].players[1].abilities.defend02_name = "Resilient Stance";
	teams[1].players[2].name = "Hulk";
	teams[1].players[2].abilities.attack01_name = "Thunderclap Smash";
	teams[1].players[2].abilities.attack02_name = "Rampaging Roar";
	teams[1].players[2].abilities.defend01_name = "Thunderous Barrier";
	teams[1].players[2].abilities.defend02_name = "Unbreakable Form";
	teams[1].players[3].name = "Black Widow";
	teams[1].players[3].abilities.attack01_name = "Widow's Sting";
	teams[1].players[3].abilities.attack02_name = "Precision Strike";
	teams[1].players[3].abilities.defend01_name = "Stealth Defense";
	teams[1].players[3].abilities.defend02_name = "Counterstrike";
	
	// Storing team teen titans player and ability names
	teams[2].players[0].name = "Robin";
	teams[2].players[0].abilities.attack01_name = "Birdarang Barrage";
	teams[2].players[0].abilities.attack02_name = "Acrobat Assault";
	teams[2].players[0].abilities.defend01_name = "Shadow Defense";
	teams[2].players[0].abilities.defend02_name = "Acrobat Evasion";
	teams[2].players[1].name = "Cyborg";
	teams[2].players[1].abilities.attack01_name = "Sonic Cannon";
	teams[2].players[1].abilities.attack02_name = "Techno Charge";
	teams[2].players[1].abilities.defend01_name = "Armor Barrier";
	teams[2].players[1].abilities.defend02_name = "Cybernetic Shield";
	teams[2].players[2].name = "Beast Boy";
	teams[2].players[2].abilities.attack01_name = "Animal Rush";
	teams[2].players[2].abilities.attack02_name = "Green Fury";
	teams[2].players[2].abilities.defend01_name = "Animal Morph Defense";
	teams[2].players[2].abilities.defend02_name = "Elasticity Shield";
	teams[2].players[3].name = "Raven";
	teams[2].players[3].abilities.attack01_name = "Dark Energy Blast";
	teams[2].players[3].abilities.attack02_name = "Mystical Assault";
	teams[2].players[3].abilities.defend01_name = "Mystic Ward";
	teams[2].players[3].abilities.defend02_name = "Telekinetic Barrier";
	
	// Storing team x-men player ability names
	teams[3].players[0].name = "Wolverine";
	teams[3].players[0].abilities.attack01_name = "Adamantium Slash";
	teams[3].players[0].abilities.attack02_name = "Berserker Rage";
	teams[3].players[0].abilities.defend01_name = "Back Handed Claw Slash";
	teams[3].players[0].abilities.defend02_name = "Adamantium Guard";
	teams[3].players[1].name = "Storm";
	teams[3].players[1].abilities.attack01_name = "Tempest Surge";
	teams[3].players[1].abilities.attack02_name = "Cyclone Strike";
	teams[3].players[1].abilities.defend01_name = "Elemental Barrier";
	teams[3].players[1].abilities.defend02_name = "Weather Shield";
	teams[3].players[2].name = "Cyclops";
	teams[3].players[2].abilities.attack01_name = "Optic Blast";
	teams[3].players[2].abilities.attack02_name = "Plasma Barrage";
	teams[3].players[2].abilities.defend01_name = "Energy Absorption";
	teams[3].players[2].abilities.defend02_name = "Visor Shield";
	teams[3].players[3].name = "Beast";
	teams[3].players[3].abilities.attack01_name = "Acrobatic Assault";
	teams[3].players[3].abilities.attack02_name = "Feline Fury";
	teams[3].players[3].abilities.defend01_name = "Enhanced Reflexes";
	teams[3].players[3].abilities.defend02_name = "Agility Barrier";
	
					
		
	// Outputting the welcome message and title graphics
	cout << "===========================================================================================================" << endl;
	cout << "                                    WELCOME TO THE BASKETBWALL WORLD CUP                                   " << endl;
	cout << "===========================================================================================================" << endl << endl;
	cout << game_title;
	cout << endl << endl << basketball_pic;
	
	// Prompting the user for the mode selection
	cout << "\n\nSelect the game mode (type 1 or 2):" << endl;
	cout << "\n[1-WORLD CUP]	 [2-Mini Game]\n";
	cout << "\nSelection: ";
	cin >> main_game.mode;
	inputError(main_game.mode, 1, 2);
	cout << endl << endl;
	
	
	
	// Output for the WORLD CUP MODE
	if (main_game.mode == 1)
	{
		// Prompting user to configure stats for the teams and players
		for (int i = 0; i < 4; i++)
			{
				cout << "===========================================================================" << endl;
				cout << "                Configure the stats for team " << teams[i].name << "                \n";
				cout << "===========================================================================" << endl;
				cout << "Enter the skill level of the " << teams[i].name << " from (1-5): ";
				cin >> teams[i].skill_level;
				inputError(teams[i].skill_level, 1, 5);
				
				// Prompting for automatic or manual configuration
				cout << "\nConfigure the stats for players Automatically or Manually?" << endl;
				cout << "\n[1-Automatically]	 [2-Manually]\n";
				cout << "\nSelection: ";
				cin >> stat_mode;
				inputError(stat_mode, 1, 2);
				
				// Randomizing stats for pre-configured player information
				for (int player_num = 0; player_num < 4; player_num++)
				{
					automaticStat(teams[i].players[player_num].teamwork);
					automaticStat(teams[i].players[player_num].endurance);
					automaticStat(teams[i].players[player_num].foul_tendency);
					automaticStat(teams[i].players[player_num].speed);
					teams[i].players[player_num].weight_magnitude = 0.5 + (1.5 * ((RAND_MAX - rand()) / static_cast<double>(RAND_MAX)));
					teams[i].players[player_num].abilities.attack01_val = (rand() % 20 + 1);
					teams[i].players[player_num].abilities.attack02_val = (rand() % 20 + 1);
					teams[i].players[player_num].abilities.defend01_val = (rand() % 20 + 1);
					teams[i].players[player_num].abilities.defend02_val = (rand() % 20 + 1);
					
					// Configuring Automatically using randomization
					if (stat_mode == 1)
					{
						automaticStat(teams[i].players[player_num].aim_accuracy);
						automaticStat(teams[i].players[player_num].agility);
						
						cout << "\nThe Aim Accuracy of " << teams[i].players[player_num].name << " from (1-5) is: " << teams[i].players[player_num].aim_accuracy;
						cout << "\nThe Agility of " << teams[i].players[player_num].name << " from (1-5) is: " << teams[i].players[player_num].agility << endl;	 
					}
					// Configuring Manually from the user
					if (stat_mode == 2)
					{
						cout << "\nEnter the Aim Accuracy of " << teams[i].players[player_num].name << ", from (1-5): ";
						cin >> teams[i].players[player_num].aim_accuracy;
						inputError(teams[i].players[player_num].aim_accuracy, 1, 5);
						cout << "Enter the Agility of " << teams[i].players[player_num].name << ", from (1-5): ";
						cin >> teams[i].players[player_num].agility;
						inputError(teams[i].players[player_num].agility, 1, 5);
					}
				}
				cout << endl;	
			}
			
			
			
			// Calculating the individual performance of all players using a performance formula  
			for (int team_num = 0; team_num < 4; team_num++)
			{
				for (int player_num = 0; player_num < 4; player_num++)
				{
					// Performance formila
					teams[team_num].players[player_num].performance = (2 * teams[team_num].skill_level * teams[team_num].players[player_num].teamwork) + (teams[team_num].players[player_num].speed * teams[team_num].players[player_num].agility) + (teams[team_num].players[player_num].aim_accuracy * teams[team_num].players[player_num].weight_magnitude) - (teams[team_num].players[player_num].endurance / 2) - (teams[team_num].players[player_num].foul_tendency);
					teams[team_num].performance += teams[team_num].players[player_num].performance;
				}	
			}
			
			// Printing information in a table format for all teams and outputting participants
			cout << "\n\nWelcome to the Basketball World Cup" << endl;
			cout << "The teams participating in the Cup are:" << endl;
			cout << "\n1.  Justice League\n"
					"2.  Avengers\n"
					"3.  Teen Titans\n"
					"4.  X-Men\n";
			
			cout << "\n\n===========================================================================" << endl;
			cout << "                Statistics for all 4 teams " << endl;
			cout << "===========================================================================" << endl << endl;
			teamStats(0); // table format
			cout << endl << endl;
			teamStats(1); // table format
			cout << endl << endl;
			teamStats(2); // table format
			cout << endl << endl;
			teamStats(3); // table format
			cout << endl << endl;
			
			
			
			// Selecting which teams will go against each other for semi finals using randomization 
			int semi_team_one, semi_team_two, semi_team_three, semi_team_four, final_team_one, final_team_two;
			
			// Selecting team one for the first semi-final
			semi_team_one = (rand() % 4);
			teams[semi_team_one].games_played += 1;
			
			// Selecting team two for the first semi-final
			semi_team_two = (rand() % 4);
			while(semi_team_two == semi_team_one)
			{
				semi_team_two = (rand() % 4);
			}
			teams[semi_team_two].games_played += 1;
			
			// Selecting team three for the second semi-final
			for (int i = 0; i < NUM_TEAMS; i++)
			{
				if (teams[i].games_played == 0)
				{
					semi_team_three = i;
					teams[i].games_played += 1;
					break;
				}
			}
			
			// Selecting team four for the second semi-final
			for (int i = 0; i < NUM_TEAMS; i++)
			{
				if (teams[i].games_played == 0)
				{
					semi_team_four = i;
					teams[i].games_played += 1;
					break;
				}
			}
			
			
			
			// Gameplay for the first semi finals  
			cout << "\n===================================================================" << endl;
			cout << "FIRST SEMI FINAL" << endl;
			cout << "\nTeam " << teams[semi_team_one].name << "   VS    Team " << teams[semi_team_two].name << endl;
			cout << "===================================================================" << endl;
			
			// Outputting the teams participating in the first semi finals to the output file 
			outputfile << "\n===================================================================" << endl;
			outputfile << "FIRST SEMI FINAL" << endl;
			outputfile << "\nTeam " << teams[semi_team_one].name << "   VS    Team " << teams[semi_team_two].name << endl;
			outputfile << "===================================================================" << endl;
			
			// Outputting the events and actions of the first semi finals using randomizer
			playGame(semi_team_one, semi_team_two, outputfile);
			
			// Assigning the winning team to the first finals team
			if (teams[semi_team_one].goals > teams[semi_team_two].goals)
			{
				final_team_one = semi_team_one;
				teams[semi_team_one].wins += 1;
			}
			else
			{
				final_team_one = semi_team_two;
				teams[semi_team_two].wins += 1;
			}
			teams[final_team_one].goals = 0;
			
			
			
			// Gameplay for the second semi finals match
			cout << "\n===================================================================" << endl;
			cout << "SECOND SEMI FINAL" << endl;
			cout << "\nTeam " << teams[semi_team_three].name << "    VS    Team " << teams[semi_team_four].name << endl;
			cout << "===================================================================" << endl;
			
			// Outputting the teams participating in the second semi finals to the output file
			outputfile << "\n===================================================================" << endl;
			outputfile << "SECOND SEMI FINAL" << endl;
			outputfile << "\nTeam " << teams[semi_team_three].name << "    VS    Team " << teams[semi_team_four].name << endl;
			outputfile << "===================================================================" << endl;
			
			// Outputting the events and actions of the second semi finals using randomizer
			playGame(semi_team_three, semi_team_four, outputfile);
			
			// Assigning the winning team to the second finals team
			if (teams[semi_team_three].goals > teams[semi_team_four].goals)
			{
				final_team_two = semi_team_three;
				teams[semi_team_three].wins += 1;
			}
			else
			{
				final_team_two = semi_team_four;
				teams[semi_team_four].wins += 1;
			}
			teams[final_team_two].goals = 0;
			
			
			
			// Gameplay for the final match
			cout << "\n===================================================================" << endl;
			cout << "FINAL MATCH" << endl;
			cout << "\nTeam " << teams[final_team_one].name << "    VS    Team " << teams[final_team_two].name << endl;
			cout << "===================================================================";
			
			// Outputting the teams participating in the finals to the output file
			outputfile << "\n===================================================================" << endl;
			outputfile << "FINAL MATCH" << endl;
			outputfile << "\nTeam " << teams[final_team_one].name << "    VS    Team " << teams[final_team_two].name << endl;
			outputfile << "===================================================================" << endl;
			
			// Outputting the events and actions of the finals match using randomizer
			playGame(final_team_one, final_team_two, outputfile);
			
			// Assigning the winner of the finals game to the winner of the world cup
			if (teams[final_team_one].goals > teams[final_team_two].goals)
			{
				teams[final_team_one].wins += 1;
				main_game.winner = teams[final_team_one].name;
			}
			else
			{
				teams[final_team_two].wins += 1;
				main_game.winner = teams[final_team_two].name;
			}
			
			
			
			// Outputting the winner of the world cup
			cout << "\n\n=====================================================" << endl;
			cout << "\tTeam " << main_game.winner << " is the World Cup Champion!" << endl;
			cout << "=====================================================" << endl;
			
			// Outputting the winner of the world cup to the output file
			outputfile << "\n=====================================================" << endl;
			outputfile << "\tTeam " << main_game.winner << " is the World Cup Champion!" << endl;
			outputfile << "=====================================================" << endl;
			
			// Calculating the total team performance of all the teams
			for (int i = 0; i < NUM_TEAMS; i++)
			{
				teams[i].performance += teams[i].total_goals * 5.4;
			}
			
			// Sorting the teams array by highest team performance to lowest team performance
			sortArrayPerformance(teams, NUM_TEAMS);
			
			// Creating a 2D array to store the summarization of the total goals, wins, and performances of all the teams 
			int scoreboard[NUM_TEAMS][3] =
			{
				{teams[0].total_goals,teams[0].wins,teams[0].performance},
				{teams[1].total_goals,teams[1].wins,teams[1].performance},
				{teams[2].total_goals,teams[2].wins,teams[2].performance},
				{teams[3].total_goals,teams[3].wins,teams[3].performance},
			};
			
			// Outputting the summarization of the total goals, wins, and performances of all the teams 
			cout << "\n=====================================================" << endl;
			cout << "\tFinal Scoreboard and Performance " << endl; 
			cout << "=====================================================" << endl << endl;
			cout << "[Num.]     [Team Name]                [Total Baskets]    [Total Wins]     [Performance]" << endl; 
			for (int i = 0; i < NUM_TEAMS; i++)
			{
				cout << setw(1) << i + 1 << setw(20) << teams[i].name << setw(-20);
				for (int j = 0; j < 3; j++)
				{
					cout << setw(19) << scoreboard[i][j];
				}
				cout << endl;
			}
			
			// Outputting the summarization of the total goals, wins, and performances of all the teams to the output file 
			outputfile << "\n=====================================================" << endl;
			outputfile << "\tFinal Scoreboard and Performance " << endl; 
			outputfile << "=====================================================" << endl << endl;
			outputfile << "[Num.]     [Team Name]                [Total Baskets]    [Total Wins]     [Performance]" << endl; 
			for (int i = 0; i < NUM_TEAMS; i++)
			{
				outputfile << setw(1) << i + 1 << setw(20) << teams[i].name << setw(-20);
				for (int j = 0; j < 3; j++)
				{
					outputfile << setw(19) << scoreboard[i][j];
				}
				outputfile << endl;
			}
			
	} // End of the WORLD CUP MODE
	
	
	
	// Output for the MINI GAME MODE
	else if (main_game.mode == 2)
	{
		// Storing user inputs and total points, and the total points for the computer
		int location, user_answer, total_points{0}, computer_total_points{0}, correct_answer;
		char user_continue;
		
		// Outputting the welcome message and game instructions
		cout << "\n==========================================================================================================" << endl;
		cout << "                                          WELCOME TO THE MINI GAME MODE                                   " << endl;
		cout << "\n\t\t    # The objective is to get the ball in the basket from different distances #" << endl;
		cout << "\n---> You get 4 attempts, and then the computer gets 4" << endl;
		cout << "---> Each attempt, you can shoot from the deep, middle, or close" << endl;
		cout << "---> The Deep gives 8 points, the middle gives 5, the close gives 3, if you score" << endl;
		cout << "---> The player with the most points wins" << endl;
		cout << "==========================================================================================================\n\n\n\n" << endl;
		
		// Outputting the gameplay for the user using a loop
		for (int i = 1; i < 5; i++)
		{
			cout << endl << endl << court_art;
			cout << "\nAttempt #: " << i << endl; 
			cout << "Which location do you want to shoot from: ";
			cin >> location;
			inputError(location, 1, 3);
			cout << endl << endl << hoops[location - 1];
			cout << "\n\nEnter a number to shoot: ";
			cin >> user_answer;
			inputError(user_answer, 1, 3);
			correct_answer = (rand() % 3 + 1);
			total_points += miniGame(location, user_answer, correct_answer);
		}
		
		// Outputting the score of the user 
		cout << "\n\nYour total score is: ";
		cout << total_points << " points" << endl;
		
		// Prompting the user to let the computer play
		cout << "\n\nNow its the computers turn" << endl;
		cout << "Enter C to continue: ";
		cin >> user_continue;
		while (!(user_continue == 'C'))
		{
			cout << "\n******************************"  << endl;
			cout << "ERROR: Invalid value entered" << endl;
			cout << "******************************"  << endl;
			cout << "Try again: ";
			cin >> user_continue;
		}
		
		// Outputting the gameplay for the computer using a loop
		if (user_continue == 'C')
		{
			for (int i = 1; i < 5; i++)
			{
				cout << endl << endl << court_art;
				cout << "\nAttempt #: " << i << endl; 
				cout << "Which location do you want to shoot from: ";
				location = (rand() % 3 + 1);
				cout << location;
				cout << endl << endl << hoops[location - 1];
				cout << "\n\nEnter a number to shoot: ";
				user_answer = (rand() % 3 + 1);
				cout << user_answer;
				correct_answer = (rand() % 3 + 1);
				computer_total_points += miniGame(location, user_answer, correct_answer);
			}
		}
		
		// Outputting the score of the user
		cout << "\n\nYour total score is: ";
		cout << computer_total_points << " points" << endl;
		
		// Determining the winner and then outputting the winner
		cout << "\n\n=============================================" << endl;
		if (total_points > computer_total_points)
		{
			cout << "\tYou win! You beat the computer" << endl;
		}
		else if (total_points == computer_total_points)
		{
			cout << "\tTie! You have the same number of points" << endl;
		}
		else
		{
			cout << "\tYou lost! The computer won" << endl;
		}
		
		// Outputting the scoreboard/summary of the game
		cout << "=============================================" << endl;
		cout << "\n     ----------- Scoreboard -----------" << endl;
		cout << "=============================================" << endl;
		cout << "\tYour total points: " << total_points << endl;
		cout << "\tComputer total points: " << computer_total_points << endl;
		cout << "=============================================" << endl;
		
		// Outputting the scoreboard/summary of the game to the output file
		outputfile << "\n     ----------- Scoreboard -----------" << endl;
		outputfile << "=============================================" << endl;
		outputfile << "\tYour total points: " << total_points << endl;
		outputfile << "\tComputer total points: " << computer_total_points << endl;
		outputfile << "=============================================" << endl;
		
	} // End of the MINI GAME MODE 
	
	return 0;
}


// Functions

/*----------------------------------------------------------------------------------*/
/* This function assigns a random value 1-5 using randomization						*/
/* Preconditions: variable/player statistic to update								*/
/* Postcondition: updates variable/player statistic									*/
int automaticStat(int& stat)
{
	stat = (rand() % 5 + 1);
	return stat;
}

/*----------------------------------------------------------------------------------*/
/* This function stores team statistics and a 2D array and outputs it				*/
/* Preconditions: team number														*/
/* Postcondition: outputs a formatted table with team statistics					*/
void teamStats(int team_num)
{
	int statistics[NUM_PLAYERS][NUM_STATS] =
	{
		{teams[team_num].players[0].aim_accuracy,teams[team_num].players[0].agility,teams[team_num].players[0].speed, teams[team_num].players[0].endurance, teams[team_num].players[0].teamwork, teams[team_num].players[0].performance},
		{teams[team_num].players[1].aim_accuracy,teams[team_num].players[1].agility,teams[team_num].players[1].speed, teams[team_num].players[1].endurance, teams[team_num].players[1].teamwork, teams[team_num].players[1].performance},
		{teams[team_num].players[2].aim_accuracy,teams[team_num].players[2].agility,teams[team_num].players[2].speed, teams[team_num].players[2].endurance, teams[team_num].players[2].teamwork, teams[team_num].players[2].performance},
		{teams[team_num].players[3].aim_accuracy,teams[team_num].players[3].agility,teams[team_num].players[3].speed, teams[team_num].players[3].endurance, teams[team_num].players[3].teamwork, teams[team_num].players[3].performance},
	};
	
	cout << "================================" << endl;
	cout << "\tTeam " << teams[team_num].name << endl; 
	cout << "================================" << endl << endl;
	cout << "[num.]          [Name]       [Aim Accuracy]   [Agility]       [Speed]      [Endurance]     [Teamwork]   [Performance]" << endl;  
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		cout << setw(1) << i + 1 << setw(20) << teams[team_num].players[i].name;
		for (int j = 0; j < NUM_STATS; j++)
		{
			cout << setw(15) << statistics[i][j];
		}
		cout << endl;
	}
	
}

/*--------------------------------------------------------------------------------------------------*/
/* This function simulates a mini game by checking if a user entered number is the correct number	*/
/* Preconditions: location(affects number of points gained), user number, and correct number		*/
/* Postcondition: returns the number of points gained												*/
int miniGame(int location, int shot, int answer)
{
	int points{0};
	
	cout << "\n--------------------------------------------------" << endl;
	if (shot == answer)
	{
		cout << "GOAL!! You scored ";
		if (location == 1)
		{
			cout << "8 points!" << endl;
			points += 8;
		}
		else if (location == 2)
		{
			cout << "5 points!" << endl;
			points += 5;
		}
		if (location == 3)
		{
			cout << "3 points!" << endl;
			points += 3;
		}
	}
	
	else 
	{
		cout << "You missed! Good try" << endl;
	}
	cout << "--------------------------------------------------" << endl;
			
	return points;
}

/*------------------------------------------------------------------------------------------------------------------*/
/* This function sorts a team array from the highest to lowest team performance using a variation of bubble sort	*/
/* Preconditions: team array, the size of the array																	*/
/* Postcondition: updates the positions of array elements															*/
void sortArrayPerformance(team array[], int array_size)
{
	// Storing variables used for swapping
	bool swap;
	team temp;
			 	
	// Sorting by descending team performances 
	do
	{
		swap = false;
		for (int count = 0; count < array_size; count++)
		{
			if (array[count].performance < array[count+1].performance)
			{
				temp = array[count];
				array[count] = array[count+1];
				array[count+1] = temp;
				swap = true;
			}
		}
	}while (swap);
}

/*------------------------------------------------------------------------------*/
/* This function simulates dirbbling in a basketball game using randomization	*/
/* Preconditions: none															*/
/* Postcondition: none															*/
void dribble()
{
	// Storing the number of dribbles
	int num_dribble;
	
	// Assiging the number of dribbles using randomization and outputting it
	num_dribble =  rand() % 6 + 1;
	for (int i = 0; i < num_dribble; i++)
	{
		cout << "\nDribbling" << endl;
	}
}

/*----------------------------------------------------------------------------------*/
/* This function simulates the jump ball proccess that occurs in basketball games	*/
/* Preconditions: 2 team numbers, the player with the ball							*/
/* Postcondition: updates which team and player has the ball						*/
void jumpBall(int team_one, int team_two, int& starting_player)
{
	int jumpball;
	jumpball = rand() % 2 + 1;
	starting_player = rand() % 4;
	
	cout << "\n-------- Jump ball --------" << endl;
	
	// Determining which team and player gets the ball			
	if (jumpball == 1)
	{
		teams[team_one].hasBall = true;
					 
		cout << "\nTeam " << teams[team_one].name << " won the jump ball and is attacking, Team " << teams[team_two].name << " is defending" << endl;
		cout << "Team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " has the ball" << endl;
	}
	else if (jumpball == 2)
	{
		teams[team_two].hasBall = true;
					 
		cout << "\nTeam " << teams[team_two].name << " won the jump ball and is attacking, Team " << teams[team_one].name << " is defending" << endl;
		cout << "Team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " has the ball" << endl;
	}	
}

/*--------------------------------------------------------------------------------------*/
/* This function simulates the scoring process that happens in basketball				*/
/* Preconditions: 2 team numbers, the player with the ball								*/
/* Postcondition: updates which team and player has the ball and may update team score	*/
void scoring(int team_one, int team_two, int& starting_player)
{
	int num_team01, num_team02, team01_star_player, team02_star_player, attack, attack01, defense, defense01;
	double team01_performance{0}, team02_performance{0};
	string attack01_name, defense01_name, attack_name, defense_name;
				
	num_team01 = rand() % 4 + 1;
	num_team02 = rand() % 4 + 1;
				
	player* team01 = new player[num_team01];
	player* team02 = new player[num_team02];
				
	for (int i = 0; i < num_team01; i++)
	{
		team01[i] = teams[team_one].players[rand() % 4];
	}
				
	for (int i = 0; i < num_team02; i++)
	{
		team02[i] = teams[team_two].players[rand() % 4];
	}
				
	for (int i = 0; i < num_team01; i++)
	{
		team01_performance += team01[i].performance;
	}
				
	for(int i =0; i < num_team02; i++)
	{
		team02_performance += team02[i].performance;
	}
				
	team01_star_player = rand() % num_team01;
	team02_star_player = rand() % num_team02;
				
	if (teams[team_one].hasBall == true)
	{
		attack = (rand() % 2 + 1);
		if (attack == 1)
		{
			team01_performance *= team01[team01_star_player].abilities.attack01_val;
			attack_name = team01[team01_star_player].abilities.attack01_name;
		}
		else
		{
			team01_performance *= team01[team01_star_player].abilities.attack02_val;
			attack_name = team01[team01_star_player].abilities.attack02_name;
		}
	}
				
	else if (teams[team_one].hasBall == false)
	{
		defense = (rand() % 2 + 1);
		if (defense == 1)
		{
			team01_performance *= team01[team01_star_player].abilities.defend01_val;
			defense_name = team01[team01_star_player].abilities.defend01_name;
		}
		else
		{
			team01_performance *= team01[team01_star_player].abilities.defend02_val;
			defense_name = team01[team01_star_player].abilities.defend02_name;
		}
	}
				
	if (teams[team_two].hasBall == true)
	{
		attack01 = (rand() % 2 + 1);
		if (attack01 == 1)
		{
			team02_performance *= team02[team02_star_player].abilities.attack01_val;
			attack01_name = team02[team02_star_player].abilities.attack01_name;
		}
		else
		{
			team02_performance *= team02[team02_star_player].abilities.attack02_val;
			attack01_name = team02[team02_star_player].abilities.attack02_name;
		}
	}
			
	else if (teams[team_two].hasBall == false)
	{
		defense01 = (rand() % 2 + 1);
		if (defense01 == 1)
		{
			team02_performance *= team02[team02_star_player].abilities.defend01_val;
			defense01_name = team02[team02_star_player].abilities.defend02_name;
		}
		else
		{
			team02_performance *= team02[team01_star_player].abilities.defend02_val;
			defense01_name = team02[team02_star_player].abilities.defend02_name;
		}
	}
				
	if (team01_performance > team02_performance && teams[team_one].hasBall == true)
	{
		if (team01_star_player != starting_player)
		{
			cout << endl << "Team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " passed the ball to " << team01[team01_star_player].name;
			starting_player = team01_star_player;
		}
		cout << endl << "SCORE! " << team01[team01_star_player].name << " scored using " << attack_name  << ".    +3 POINTS" << endl;
		teams[team_two].hasBall = true;
		teams[team_one].hasBall = false;
		starting_player = rand() % 4;
		cout << "\nTeam " << teams[team_two].name << " is attacking, team " << teams[team_one].name << " is defending" << endl;
		cout << "Team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " has the ball" << endl;
		teams[team_one].goals += 3;
		teams[team_one].total_goals += 3;  
	}
				
	else if (team01_performance > team02_performance && teams[team_one].hasBall == false)
	{
		cout << endl << "Team " << teams[team_one].name << " player " << team01[team01_star_player].name << " prevents team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " from scoring using " << defense_name << endl;
	}
				
	if (team02_performance > team01_performance && teams[team_two].hasBall == true)
	{
		if (team02_star_player != starting_player)
		{
			cout << endl << "Team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " passed the ball to " << team02[team02_star_player].name;
			starting_player = team02_star_player;
		}
		cout << endl << "SCORE! " << team02[team02_star_player].name << " scored using " << attack01_name << ".    +3 POINTS" << endl;
		teams[team_two].goals += 3;
		teams[team_two].total_goals += 3; 
		teams[team_two].hasBall = false;
		teams[team_one].hasBall = true;
		starting_player = rand() % 4;
		cout << "\nTeam " << teams[team_one].name << " is attacking, team " << teams[team_two].name << " is defending" << endl;
		cout << "Team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " has the ball" << endl;  
	}
				
	else if (team02_performance > team01_performance && teams[team_two].hasBall == false)
	{
		cout << endl << "Team " << teams[team_two].name << " player " << team02[team02_star_player].name << " prevents team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " from scoring using " << defense01_name << endl;
	}
				
	delete[] team01;
	delete[] team02;
}

/*------------------------------------------------------------------------------------------*/
/* This function simulates 4 types of fouls that could happen in basketball	    			*/
/* Preconditions: 2 team numbers, the player with the ball, and hoop ascii art				*/
/* Postcondition: updates which team and player has the ball, and maybe updates the score	*/
void fouls(int team_one, int team_two, int& starting_player, string hoop)
{
	foul game_foul;
	int score_val, user_guess;
				
				
	game_foul.num = (rand() % 4);
	game_foul.guilty_player = (rand() % 4);
	game_foul.innocent_player = (rand() % 4);
	starting_player = (rand() % 4);
				
	if (teams[team_one].hasBall == true)
	{
		if (game_foul.num >= 0 && game_foul.num <= 1)
		{
			teams[team_one].hasBall = false;
			teams[team_two].hasBall = true;
			cout << endl << game_foul.foul_type[game_foul.num] << " from team " << teams[team_one].name << " player " << teams[team_one].players[game_foul.guilty_player].name << " against team " << teams[team_two].name << " player " << teams[team_two].players[game_foul.innocent_player].name << endl;
			cout << "Possession of the ball goes to team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << endl;
		}
		else if (game_foul.num >= 2 && game_foul.num <= 3)
		{
			cout << endl << game_foul.foul_type[game_foul.num] << " from team " << teams[team_one].name << " player " << teams[team_one].players[game_foul.guilty_player].name << " against team " << teams[team_two].name << " player " << teams[team_two].players[game_foul.innocent_player].name << endl;
			cout << "Team " << teams[team_two].name << " player " << teams[team_two].players[game_foul.innocent_player].name << " gets a free throw " << endl;
			cout << endl << hoop;
			score_val = (rand() % 3 + 1);
			cout << "\nEnter a number (1-3) to shoot: ";
			cin >> user_guess;
			inputError(user_guess, 1, 3);
			if (user_guess == score_val)
			{
				teams[team_two].hasBall = false;
				teams[team_one].hasBall = true;
				teams[team_two].goals += 1;
				teams[team_two].total_goals += 1;
				cout << "Team " << teams[team_two].name << " SCORES!    +1 POINT" << endl;
				cout << "\nTeam " << teams[team_one].name << " is attacking, team " << teams[team_two].name << " is defending" << endl;
				cout << "Team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " has the ball";
			}
			else
			{
				teams[team_two].hasBall = true;
				teams[team_one].hasBall = false;
				cout << "Team " << teams[team_two].name << " MISSES" << endl;
				cout << "\nTeam " << teams[team_two].name << " is attacking, team " << teams[team_one].name << " is defending" << endl;
				cout << "Team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " has the ball" << endl;
			}
		}
	}
				
	else if (teams[team_two].hasBall == true)
	{
		if (game_foul.num >= 0 && game_foul.num <= 1)
		{
			teams[team_two].hasBall = false;
			teams[team_one].hasBall = true;
			cout << endl << game_foul.foul_type[game_foul.num] << " foul from team " << teams[team_two].name << " player " << teams[team_two].players[game_foul.guilty_player].name << " against team " << teams[team_one].name << " player " << teams[team_one].players[game_foul.innocent_player].name << endl;
			cout << "Possession of the ball goes to team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << endl;
		}
		else if (game_foul.num >= 2 && game_foul.num <= 3)
		{
			cout << endl << game_foul.foul_type[game_foul.num] << " foul from team " << teams[team_two].name << " player " << teams[team_two].players[game_foul.guilty_player].name << " against team " << teams[team_one].name << " player " << teams[team_one].players[game_foul.innocent_player].name << endl;
			cout << "Team " << teams[team_one].name << " player " << teams[team_one].players[game_foul.innocent_player].name << " gets a free throw " << endl;
			cout << endl << hoop;
			score_val = (rand() % 3 + 1);
			cout << "\nEnter a number (1-3) to shoot: ";
			cin >> user_guess;
			inputError(user_guess, 1, 3);
			if (user_guess == score_val)
			{
				teams[team_one].hasBall = false;
				teams[team_two].hasBall = true;
				teams[team_one].goals += 1;
				teams[team_one].total_goals += 1;
				cout << "Team " << teams[team_one].name << " SCORES!    +1 POINT" << endl;
				cout << "\nTeam " << teams[team_two].name << " is attacking, team " << teams[team_one].name << " is defending" << endl;
				cout << "Team " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " has the ball";
			}
			else
			{
				teams[team_one].hasBall = true;
				teams[team_two].hasBall = false;
				cout << "Team " << teams[team_one].name << " MISSES" << endl;
				cout << "\nTeam " << teams[team_one].name << " is attacking, team " << teams[team_two].name << " is defending" << endl;
				cout << "Team " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " has the ball" << endl;
			}
		}
	}
}

/*----------------------------------------------------------------------------------*/
/* This function simulates intercepting a ball from the opposing team in basketball	*/
/* Preconditions: 2 team numbers, the player with the ball							*/
/* Postcondition: updates which team and player has the ball						*/
void interception(int team_one, int team_two, int& starting_player)
{
	int old_player;
				
	old_player = starting_player;
	starting_player = rand() % 4;
					
	if (teams[team_one].hasBall == true)
	{
		teams[team_one].hasBall = false;
		teams[team_two].hasBall = true;
				
		cout << "\nTeam " << teams[team_two].name << " player " << teams[team_two].players[starting_player].name << " has intercepted the ball from Team " << teams[team_one].name << " player " << teams[team_one].players[old_player].name << endl;
		cout << "Team " << teams[team_two].name << " is attacking, team " << teams[team_one].name << " is defending" << endl;  
	}
				
	else if (teams[team_two].hasBall == true)
	{
		teams[team_two].hasBall = false;
		teams[team_one].hasBall = true;
					
		cout << "\nTeam " << teams[team_one].name << " player " << teams[team_one].players[starting_player].name << " has intercepted the ball from Team " << teams[team_two].name << " player " << teams[team_two].players[old_player].name << endl;
		cout << "Team " << teams[team_one].name << " is attacking, team " << teams[team_two].name << " is defending" << endl;
	}
}

/*----------------------------------------------------------------------------------*/
/* This function simulates a basketball game taken into overtime					*/
/* Preconditions: 2 team numbers													*/
/* Postcondition: adds 1 to the score of one the teams								*/
void overtime(int team_one, int team_two)
{
		int random_value;
		random_value = (rand() % 2 + 1);
					
		cout << "\n\n--------- Overtime Round ---------" << endl;
		if (random_value == 1)
		{
			teams[team_one].goals += 1;
			teams[team_one].total_goals += 1;
		}
		else if (random_value == 2)
		{
			teams[team_two].goals += 1;
			teams[team_two].total_goals += 1;
		}
}

/*------------------------------------------------------------------------------------------*/
/* This function prints the results of a basketball round to the screen and a output file	*/
/* Preconditions: 2 team numbers, 1 output file												*/
/* Postcondition: assigns a winner, outputs results, modifies output file					*/
void displayResults(int team_one, int team_two, ofstream& outputfile)
{
	string winner;
					
	if (teams[team_one].goals > teams[team_two].goals)
	{
		winner = teams[team_one].name;
	}
	else
	{
		winner = teams[team_two].name;
	} 
					
	cout << "\n\n================================" << endl;
	cout << "\t  Scoreboard                      " << endl;
	cout << "\nTeam " << teams[team_one].name << ": " << teams[team_one].goals << " Baskets" << endl;
	cout << "Team " << teams[team_two].name << ": " << teams[team_two].goals << " Baskets" << endl;
	cout << "\nTeam " << winner << " won the Game" << endl;
	cout << "================================" << endl << endl;
					
				
	outputfile << "\n\t  Scoreboard                      " << endl;
	outputfile << "\nTeam " << teams[team_one].name << ": " << teams[team_one].goals << " Baskets" << endl;
	outputfile << "Team " << teams[team_two].name << ": " << teams[team_two].goals << " Baskets" << endl;
	outputfile << "\nTeam " << winner << " won the Game" << endl;
	outputfile << "===================================================================\n\n" << endl << endl;
					
	teams[team_two].hasBall = false;
	teams[team_one].hasBall = false;
}

/*------------------------------------------------------------------------------------------*/
/* This function simulates actions and events that happen in a game using randomization		*/
/* Preconditions: 2 team numbers, an output file											*/
/* Postcondition: outputs, displays results, modifies output file							*/
void playGame(int team_one, int team_two, ofstream& outputfile)
{
	int starting_player, num_plays, selected_play;
	char start_round;
	num_plays = (rand() % 3 + 8);
				
	cout << "\nPress 'S' to start the round: ";
	cin >> start_round;
	while (!(start_round == 'S'))
		{
			cout << "\n******************************"  << endl;
			cout << "ERROR: Invalid value entered" << endl;
			cout << "******************************"  << endl;
			cout << "Try again: ";
			cin >> start_round;
		}
				
	for (int i = 1; i < num_plays + 1; i++)
	{
		selected_play = (rand() % 11 + 1);
		if (i == 1)
		{
			jumpBall(team_one, team_two, starting_player);
			dribble();
		}
						
		else if (selected_play >= 1 && selected_play <= 6)
		{
			scoring(team_one, team_two, starting_player);
			dribble();
		}
		else if (selected_play >= 7 && selected_play <= 9)
		{
			interception(team_one, team_two, starting_player);
			dribble();
		}
		else if (selected_play >= 10 && selected_play <= 11)
		{
			fouls(team_one, team_two, starting_player, hoop);
			dribble();
		}
	}

				
	if (teams[team_one].goals == teams[team_two].goals)
	{
		overtime(team_one, team_two);
	}
	displayResults(team_one, team_two, outputfile);
}

/*----------------------------------------------------------*/
/* This function handles int range value errors        	 	*/
/* Preconditions: variable to check, 2 numbers for the range*/
/* Postcondition: none										*/
void inputError(int &input, int x, int y)
{
		while (!(input >= 0 && input <= y))
		{
			cout << "\n******************************"  << endl;
			cout << "ERROR: Invalid value entered" << endl;
			cout << "******************************"  << endl;
			cout << "Try again, type a num " << x << " - " << y << ":  ";
			cin >> input;
		}
}

