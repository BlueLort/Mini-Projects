#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <iostream>
#include <regex>
#include <cstring>
#include <fstream>
#include <chrono>
#include <ctime>

char LOG_FILE[256];
#define LOG_FILE_NAME "/Log.txt"
#define SYS_CLK std::chrono::system_clock
#define TIME_NOW SYS_CLK::to_time_t(SYS_CLK::now());
/*LOG & LOG_TIME will require '{' & '}' to resolve scoping issues
	{Easy fix for now}
*/

//LOG is to print to a file and close it immediately without timestamp
#define LOG(str)                                                  \
    std::ofstream oFile(LOG_FILE, std::ios::app | std::ios::out); \
    oFile << str << std::endl;                                    \
    oFile.close()

//LOG_TIME is to print to a file and close it immediately with timestamp
#define LOG_TIME(str)                                             \
    std::ofstream oFile(LOG_FILE, std::ios::app | std::ios::out); \
    time_t curTime = TIME_NOW;                                    \
    char *buffer = std::ctime(&curTime);                          \
    buffer[strlen(buffer) - 1] = 0;                               \
    oFile << "[ " << buffer << " ] " << str << std::endl;         \
    oFile.close()

//execute user input string vector
inline void execCommand(const std::vector<std::string>& args);
//convert string vector to char** argv
inline void setArgs(const std::vector<std::string>& args, char** argv, int len);
//helper function to convert from int to string
inline std::string toString(uint32_t num);
//callback for SIGCHLD signal
void procEnd(int sig)
{
	LOG_TIME("Child process was terminated");
}
int main()
{
	//keep the log.txt file in absolute path so when user use CD the logfile path does not change
	getcwd(LOG_FILE, 256);
	strcat(LOG_FILE, LOG_FILE_NAME);

	//regex to match every thing typed in the line
	std::regex reg("(\\S+)");
	//matcher required to obtain data from regex search
	std::smatch match;
	{
		LOG("-------------------------UNIX SHELL-------------------------");
	}
	{
		LOG_TIME("Start Of New Session ! ");
	}
	//set approptiate callback function on termination.
	signal(SIGCHLD, procEnd);
	//terminated if user typed exit();
	while (true)
	{
		//obtain line from user
		std::string input;
		std::getline(std::cin, input);
		{
			LOG_TIME("User Entered : " + input);
		}
		//process(command) & args is stored in args in the same written ordered
		std::vector<std::string> args;
		//get each string from the line and push it to the args vec.
		while (std::regex_search(input, match, reg))
		{
			//str(0) is whole match str(1) is first match
			//yes here we have 1 matching group but its just good convention to get str(1)
			args.emplace_back(match.str(1));
			input = match.suffix().str();
		}
		if (args.size() == 0)
		{
			//Empty Line
			continue;
		}

		//CD command executed on parent process so any child work from the given directory.
		if (args[0].length() == 2 && args.size() >= 2 && toupper(args[0][0]) == 'C' && toupper(args[0][1]) == 'D')
		{
			{
				LOG_TIME("Changing Directory in parent process");
			}
			char dir[256];// to store current working directory
			{
				LOG_TIME("Previous directory :" + std::string(getcwd(dir, 256)));
			}
			//get path from user input
			std::string path = args[1];
			for (int i = 2; i < args.size(); i++)path += " " + args[i];
			int changeResult = chdir(path.c_str());
			if (changeResult == 0)
			{
				LOG_TIME("Current directory :" + std::string(getcwd(dir, 256)));
			}
			else {
				LOG_TIME("Failed to change directory !");
			}
			continue;
		}
		//terminate shell condition
		if (args[0] == "exit")
		{
			{
				LOG_TIME("Exit Command Recieved !");
			}
			exit(0);
		}
		uint32_t procID = fork();
		std::string procID_S = toString(procID);
		if (procID == 0) //i'm the child process
		{

			execCommand(args);
		}
		//execute log effect in the parent only as the child
		//will terminate anyway
		{
			LOG_TIME("Process started with ID: " + procID_S);
		}
		uint32_t waitID = 0;
		if (args[args.size() - 1] != "&")
		{
			waitID = wait(NULL);
			//make sure the the terminated process is the one we are waiting for
			while (waitID != procID)
			{
				waitID = wait(NULL);
			}
			std::string waitID_S = toString(waitID);
			{
				LOG_TIME("Waiting was issued for Process " + waitID_S);
			}
		}
	}

	return 0;
}
void execCommand(const std::vector<std::string>& args)
{
	int len = args.size();

	//if sent & we ignore it so it doesnt be sent to the apps
	//as command line arg
	if (args[len - 1] == "&")
		len--;

	char* argv[len + 1];

	//set args content into the argv char* array
	setArgs(args, argv, len);

	//Exectute the command with it's proper args
	uint32_t execID = execvp(argv[0], argv);
	if (execID == -1) //Error
	{
		{
			LOG_TIME("Error Encounterd using execvp() ! returned -1");
		}
		std::cerr << "Error Encounterd using execvp() !" << std::endl;
		std::cerr << args[0] << " is either invalid or undefined command" << std::endl;
		/* Executed only if error happened because execvp take control of proc*/
		for (int i = 0; i < len; i++)
		{
			free(argv[i]);
		}
		exit(-1);
	}
}
void setArgs(const std::vector<std::string>& args, char** argv, int len)
{
	for (int i = 0; i < len; i++)
	{
		char* buffer = (char*)malloc(args[i].length() * sizeof(char));
		argv[i] = strcpy(buffer, args[i].c_str());
	}
	argv[len] = NULL; //its required so execvp run successfully
}
std::string toString(uint32_t num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}
