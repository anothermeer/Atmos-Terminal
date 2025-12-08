// -----------------------------------------------------------------------------------
// |           _                         _______                  _             _    |
// |      /\  | |                       |__   __|                (_)           | |   |
// |     /  \ | |_ _ __ ___   ___  ___     | | ___ _ __ _ __ ___  _ _ __   __ _| |   |
// |    / /\ \| __| '_ ` _ \ / _ \/ __|    | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | |   |
// |   / ____ \ |_| | | | | | (_) \__ \    | |  __/ |  | | | | | | | | | | (_| | |   |
// |  /_/    \_\__|_| |_| |_|\___/|___/    |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_|   |
// |                                                                                 |
// -----------------------------------------------------------------------------------

//                     V E R S I O N   1 . 0 . 0 - C + + [private beta]
//                         B U I L D   W I N - 1 . 0 

//     Local Vars : 
//           termver       =  Terminal version
//           usrname       =  Current user name
//           cmd           =  The command placeholder

//     Known Issues : 
//           *nothing!*

//     Created Commands :
//           quotedOutput(type, message);
//			 cls();

//     Error reference :
//           err_invalQOtype            = invalid QuotedOutput type
//           err_invalInterCmd          = invalid internal command
//           err_unknowninterr          = unknown internal error
//           err_getwinmajvergonebad    = error getting windows version
//           err_psoutrederr            = powershell output redirect error
//           err_loadBatchFileFailed    = error loading batch file
//			 err_invalrndnumparam       = invalid random number parameter
//           err_createpipenotsuccess   = error creating pipe for outputing

//     Pending commands to add :
//           liltool()     - a tool to do anything (maybe)
//           idkwhattocallthisgame()  - A little idle game

//     Working on tasks :
//           1. continue porting the code from batch ver
//           2. slowly abandon batch ver
//           3. make all functions functional

//     For me :
//     use this to compile: g++ --verbose -o Atmos-Terminal.exe Atmos-Terminal.cpp -static-libgcc -static-libstdc++ --static
//     remember to put semicolon!!!


//      W A R N I N G : You are looking into the source code of atmos terminal.
//                      You are editing the source code and you know what you are doing.
//                           ! ! !    EDIT   IT   CAREFULLY    !!!

//         N O T E : This C++ version is ported from batch version :)

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <map>
//import random
#include <functional>
#include <cstdlib>
#include <algorithm>

//#define _WIN32_WINNT 0x0600
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;
typedef std::vector<std::string> vecstr;
typedef std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> uomap;

vecstr dummy;

// functions

string getWinVer() {
	// oh god...
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	
	if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
		return to_string(osvi.dwMajorVersion);
	} else {
		cout << "[ERROR] Error getting Windows version! Report it as a bug! [err_getwinmajvergonebad]" << endl;
		return "unknown";
	}
}

void useBatch(string file) {
	WORD batfile;
	
	if (file == "mas_aio.bat") {
		batfile = 101;
	}
	
	// Load the batch file resource from the executable
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(batfile), RT_RCDATA);
    if (hRes == NULL) {
        cerr << "[ERROR] Failed to find batch file resource! Report it as a bug! [err_loadBatchFileFailed]" << endl;
        return;
    }

    // Load the resource into memory
    HGLOBAL hResData = LoadResource(NULL, hRes);
    if (hResData == NULL) {
        cerr << "[ERROR] Failed to load batch file resource! Report it as a bug! [err_loadBatchFileFailed]" << endl;
        return;
    }

    // Lock the resource to access its data
    LPVOID pResData = LockResource(hResData);
    DWORD resSize = SizeofResource(NULL, hRes);

    // Write the resource content (batch file) to a temporary file
    const char* tempBatchFile = "tmpbat_masaio.bat";
    ofstream outFile(tempBatchFile, ios::binary);
    if (!outFile) {
        cerr << "[ERROR] Failed to create temporary batch file! [err_loadBatchFileFailed]" << endl;
        return;
    }
    outFile.write((const char*)pResData, resSize);
    outFile.close();

    // Execute the batch file using system()
    cout << "Running batch file..." << std::endl;
    if (system(tempBatchFile) != 0) {
        cerr << "[ERROR] Failed to execute batch file! [err_loadBatchFileFailed]" << endl;
        return;
    }

    // Optionally delete the temporary batch file
    if (remove(tempBatchFile) != 0) {
        cerr << "Failed to delete temporary batch file!" << endl;
    }
}

void sleep(int milsec) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milsec));
}

string checkPlatform() {
	#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
		return "windows";
	#elif defined(__CYGWIN__)
		return "cygwin environment";
	#elif defined(__unix__)
	    // bro, unix bad, linux good, use linux.
		return "unix";
	#elif defined(__GNU__)
		return "GNU";
	#elif defined(__GNU_hurd__)
		return "GNU/Hurd";
	#elif defined(__gnu_linux__)
		return "GNU/linux";
	#elif defined(__FreeBSD_kernel__) || defined(__FreeBSD__) || defined(__GLIBC__)
		return "GNU/kFreeBSD (FreeBSD)";
	#elif defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__MidnightBSD__)
		return "BSD environment"
	#elif defined(__ANDROID__)
		return "Android";
	// who use these OS anyway?
	#elif defined(__bg__)
		return "Blue Gene";
	#elif defined(__BEOS__)
		return "BeOS";
	#else
		cout << "[WARN] Your machine does not support this function, request it to become supported!";
	#endif
}

bool isUnixLike(const std::string& platform) {
	static const vecstr unixLikeOS = {
		"unix",
		"GNU",
		"GNU/Linux",
		"GNU/Hurd",
		"GNU/kFreeBSD",
		"BSD environment",
		"Android",
	};
	return find(unixLikeOS.begin(), unixLikeOS.end(), platform) != unixLikeOS.end();
}

string getHostname() {
	string hn;
	string hnr;
	string platform = checkPlatform();
	if (platform == "windows") {
		const char* hn = getenv("COMPUTERNAME");
		hnr = hn ? hn : "unknown_hostname";
	} else {
		const char* hn = getenv("HOSTNAME");
		hnr = hn ? hn : "unknown_hostname";
	}
	return hnr;
}

void cls(const vecstr& params) {
	string platform = checkPlatform();
	
	if (platform == "windows") {
		// windows is complex as shit
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD written;
		
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
		COORD topleft = {0,0};
		DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
		
		FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topleft, &written);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, topleft, &written);
		SetConsoleCursorPosition(hConsole, topleft);
	} else if (isUnixLike(platform)) {
		cout << "\033[2J\033[H";
	} else {
		cerr << "[WARN] Your OS does not support clear screen function.";
	}
	
}

void ph() {
	// not what you think! it's placeholder >:(
	cout << "Stay tune for the function! This is a trailer :)" << endl;
}

string getSysUsrName() {
	const char* username = std::getenv(
        #ifdef _WIN32
            "USERNAME"
        #else
            "USER"
        #endif
    );
	return (username != nullptr) ? username : "Unknown";
}


// GLOBAL VARIABLESSSSSS
// although it's a bit awkward to be here
const string termver = "CPP-1.0.0-WIN";
string usrname = getSysUsrName();
string cpf = "cmd.";   //command prefix, abandoned
bool verbosemode = false;

///////////////////////////////////////////////

void printInAppHelp(const vecstr& params) {
	cout << "Legend: [] = required | <> = optional | {} = alternate command";
	cout << "\n";
	cout << "[General Commands]" << endl;
	cout << "help                - display this menu in the terminal" << endl;
	cout << "ver                 - display terminal version in the terminal" << endl;
	cout << "clear               - clears the terminal" << endl;
	cout << "exit                - exits the terminal pecefully." << endl;
	cout << "\n";
	cout << "[File Processing]" << endl;
	cout << "pwd                 - display current directory" << endl;
	cout << "cd [FolderName]     - change current directory to target directory" << endl;
	cout << "mkfile [FileName]   - creates an empty file" << endl;
	cout << "mkdir [FolderName]  - creates an empty folder" << endl;
	cout << "ls <Path>           - list out current directory's content" << endl;
	cout << "\n";
	cout << "[Advanced Commads]" << endl;
	cout << "psexec {pex}        - create a Powershell instance" << endl;
	cout << "cmdinteract {citr}  - create an interactive Command Prompt instance" << endl;
	cout << "\n";
	cout << "[External Tools]" << endl;
	cout << "liltool             - start liltool" << endl;
	cout << "mas                 - start MAS (Microsoft Activation Script by massgrave.dev)" << endl;
}

void printHelp() {
	cout << "Atmos Terminal version " << termver << "\n";
    cout << "[Help Menu]\n\n";
    cout << "Run Atmos Terminal to execute the commands!\n\n";
    cout << "Command Line Options:\n";
    cout << "  -V / --version    - prints terminal version and exit\n";
    cout << "  -H / --help       - prints help and exit\n";
	cout << "  --osinfo          - prints system info and exit\n";
    cout << "  --verbose         - start Atmos Terminal and enters verbose mode\n";
    cout << "\nIn-app Commands:\n";
	printInAppHelp(dummy);
}

void printVer() {
	cout << "Atmos Terminal version " << termver << endl;
}

string getCmd() {
	string cmd;
	cout << usrname << "> "; getline(cin, cmd); cout << endl;
	return cmd;
	
	// cout << usrname << "> "; cin >> cmd; cout << endl;
}

void quotedOutput(const string& type, const string& text) {
	const map<string, string> quotetype = {
		{"debug", "[DEBUG]"},
		{"warning", "[WARN]"},
		{"error", "[ERROR]"}
	};
	
	auto qtype_it = quotetype.find(type);
	// even god cannot understand this...
	if (qtype_it != quotetype.end()) {
		if (type == "error" || type == "warning") {
			cerr << qtype_it->second << " " << text << endl;
		} else {
			cout << qtype_it->second << " " << text << endl;
		}
	} else {
		cerr << "[ERROR] Unknown verbose type: " << type << " , report it as a bug! [err_invalQOtype]" << endl;
	}
}
////////////////////////////////////////////////////////////
////////////////        Command Area         ///////////////

// PLEASE add this to every function parameter: const vecstr& params
// even the function does nothing.

void printtermver(const vecstr& params) {
	if (!params.empty()) {
		quotedOutput("warning", "The command does not accept any parameter/arguments.");
	} else {
		cout << termver << endl;
	}
}

void pwd(const vecstr& params) {
	if (!params.empty()) {
		quotedOutput("warning", "The command does not accept any arguments.");
		return;
	}
	
	try {
		fs::path currdir = fs::current_path();
		cout << "Current Directory: " << currdir.string() << endl;
	} catch (fs::filesystem_error& eeeee) {
		quotedOutput("warning", string("Could not get current directory, details: ")+eeeee.what());
	}
}

void exitterm(const vecstr& params) {
	cout << "cleaning up...";
	cout << "Done.\nBye Bye!";
	exit(0);
}

void mkfil(const vecstr& params) {
	if (params.empty()) {
		quotedOutput("warning", "No file name provided. Command usage: mkfile [filename]");
		return;
	}
	
	const string& filename = params[0];
	ofstream outFile(filename, std::ios::out);
	if (outFile) {
		cout << "File '" << filename << "' created successfully.";
	} else {
		quotedOutput("warning", string("File '")+filename+string("' was not created due to an unknown error. [err_unknowninterr]"));
	}
}

void mkfol(const vecstr& params) {
	if (params.empty()) {
		quotedOutput("warning", "No folder name provided. Command usage: mkdir [foldername]");
		return;
	}
	
	const string& foldername = params[0];
	
	try {
		if (fs::create_directory(foldername)) {
			cout << "Folder '" << foldername << "' created successfully.";
		} else {
			quotedOutput("warning", "Folder '"+foldername+"' was not created due to an unknown error. [err_unknowninterr]");
		}
	} catch (const fs::filesystem_error& eeeee) {
		quotedOutput("warning", string("Could not create folder '")+foldername+string("', details: ")+eeeee.what());
	}
}


void cdir(const vecstr& params) {
	if (params.empty()) {
		quotedOutput("warning", "No directory/folder name provided. Command usage: cd [foldername]");
		return;
	}
	
	const string& dir = params[0];
	
	try {
		fs::current_path(dir);
	} catch (const fs::filesystem_error& eeeee) {
		quotedOutput("warning", string("Could not change directory to '")+dir+string("', details: ")+eeeee.what());
	}
}

void getDirContent(const vecstr& params) {
	
	string lspath;
	
	if (params.empty()) {
		lspath = ".";
	} else {
		lspath = params[0];
	}
	
	if (fs::is_directory(lspath)) {
		for (const auto& entry : fs::directory_iterator(lspath)) {
			cout << entry.path() << endl;
		}
	} else {
		quotedOutput("warning", lspath+string(" is not a valid directory/folder."));
	}
}

void renamef(const vecstr& params) {ph();}

bool isGUIapp(const string& command) {
	// design dedicated for cmd and powershell instances.
	char fullpath[MAX_PATH];
	
	if (SearchPath(NULL, command.c_str(), ".exe", MAX_PATH, fullpath, NULL) == 0) {
		return false;
	}
	
	DWORD binType;
	
	if (GetBinaryType(fullpath, &binType)) {
		if (binType == SCS_WINDOWS_GUI) {
			return true;
		}
	}
	
	return false;
}

void cmdinteract(const vecstr& params) {
	// if (params.empty()) {
		// quotedOutput("warning", "No command provided. Command usage: cmdexec [command]");
		// return;
	// }
	
	HANDLE hReadPipe, hWritePipe;
	HANDLE hInputRead, hInputWrite;
	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
		quotedOutput("error", "Error creating cmd pipe for output! [err_createpipenotsuccess]");
		return;
	}
	if (!CreatePipe(&hInputRead, &hInputWrite, &sa, 0)) {
		quotedOutput("error", "Error creating cmd pipe for input! [err_createpipenotsuccess]");
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);
		return;
	}
	
	
	STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi;
    
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.hStdOutput = hWritePipe;
	si.hStdError = hWritePipe;
	si.hStdInput = hInputRead;
	si.wShowWindow = SW_HIDE; // hide it for nothing :)
	
	if (!CreateProcess(
            NULL,
            (LPSTR)"cmd.exe",            // Command line to run
            NULL,                        // Process security attributes
            NULL,                        // Thread security attributes
            TRUE,                        // Inherit handles
            0,                           // Creation flags
            NULL,                        // Environment
            NULL,                        // Current directory
            &si,                         // Startup info
            &pi)                         // Process information
        ) {
			DWORD errcode = GetLastError();
			quotedOutput("error", "Failed to start command prompt instance. Error code: " + to_string(errcode));
			CloseHandle(hReadPipe);
			CloseHandle(hWritePipe);
			CloseHandle(hInputRead);
			CloseHandle(hInputWrite);
			return;
		}
	
        // Close useless handle
        CloseHandle(hWritePipe);
		CloseHandle(hInputRead);
		
		cout << "Initializing cmd.exe instance..." << endl;
		
		char buffer[4096];
		DWORD bytesRead, bytesWritten;
		DWORD availableBytes = 0;
		string userInput;
		
		cout << "cmd.exe instance successfully spawned!" << endl;
		
		while (true) {
			cout << "cmd@" + usrname + "> ";
			getline(cin, userInput);
			userInput += "\n";

			// Exit if user types "exit"
			if (userInput == "exit\n") break;

			string command = userInput.substr(0, userInput.find(' '));
			
			if (isGUIapp(command)) {
				// bruh ChatGPT blocked it...
				if (CreateProcess(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
				} else {
					quotedOutput("error", "Failed to launch GUI application: \"" + command + "\"");
				}
				continue;
			}
			
			if (!WriteFile(hInputWrite, userInput.c_str(), userInput.size(), &bytesWritten, NULL)) {
				quotedOutput("error", " Failed to send command to cmd.exe instance!");
				break;
			}
			
			while (true) {
				if (!PeekNamedPipe(hReadPipe, NULL, 0, NULL, &availableBytes, NULL) || availableBytes == 0) {
					sleep(100);
					break;
				}
				if (!ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) || bytesRead == 0) {
					break;
				}
				
				buffer[bytesRead] = '\0';
				cout << buffer;
			}
		}
		
		// Close all handles
		CloseHandle(hReadPipe);
		CloseHandle(hInputWrite);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		
}

void cmdexec(const vecstr& params) {
	if (params.empty()) {
		quotedOutput("warning", "No command provided. Command usage: cmdexec [command]");
		return;
	}
	
	STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi;
	
	if (!CreateProcess(
            NULL,
            "cmd.exe /C ",            // Command line to run
            NULL,                        // Process security attributes
            NULL,                        // Thread security attributes
            TRUE,                        // Inherit handles
            0,                           // Creation flags
            NULL,                        // Environment
            NULL,                        // Current directory
            &si,                         // Startup info
            &pi)                         // Process information
        ) {
			DWORD errcode = GetLastError();
			quotedOutput("error", "Failed to start command prompt instance. Error code: " + to_string(errcode));
			return;
		}
}

void psexec(const vecstr& params) {
    if (params.empty()) {
		quotedOutput("warning", "No command provided. Command usage: psexec [command]");
		return;
	}

	ostringstream oss;
	for (const auto& param : params) {
		oss << param << " ";
	}
	
	string usepscmd = oss.str();
	usepscmd.pop_back();
    std::string command = "powershell.exe -ExecutionPolicy Bypass -Command \"" + usepscmd + "\"";

	// OH MY GOD WHY WINDOWS, WHY!!!!
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

	// pipes to output the output from powershell
	HANDLE hStdOutRead, hStdOutWrite;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
	
	if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0)) {
        quotedOutput("error", "Failed to create pipe for output redirection. Report it as a bug! [err_psoutrederr]");
        return;
    }
    SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);

    si.hStdOutput = hStdOutWrite;
    si.hStdError = hStdOutWrite;

    if (CreateProcess(
            NULL,
            const_cast<char*>(command.c_str()), // Command line to run
            NULL,                        // Process security attributes
            NULL,                        // Thread security attributes
            FALSE,                       // Inherit handles
            CREATE_NO_WINDOW,            // Creation flags
            NULL,                        // Environment
            NULL,                        // Current directory
            &si,                         // Startup info
            &pi)                         // Process information
        ) {
		
		CloseHandle(hStdOutRead);
		
		char buffer[4096];
		DWORD bytesRead;
		string output;
		while (ReadFile(hStdOutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            output += buffer;
		}
		
		cout << output << endl;
		
        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
		CloseHandle(hStdOutRead);
    } else {
		DWORD errcode = GetLastError();
		quotedOutput("error", "Failed to execute PowerShell command. Error code: " + to_string(errcode));
	}
}

void masentfallback() {
	useBatch("mas_aio.bat");
}

void masent(const vecstr& params) {
	string nwinver = getWinVer();
	if (nwinver != "unknown" && stoi(nwinver) > 8) {
		vecstr execpscmd = {"irm", "https://get.activated.win", "|", "iex"};
		psexec(execpscmd);
	} else if (nwinver == "unknown") {
		quotedOutput("error", "Error getting Windows version! Report it as a bug! [err_getwinmajvergonebad]");
	} else {
		quotedOutput("warning", "Your OS is Windows 8 or lower, will use legacy");
		masentfallback();
	}
}

void liltoolent(const vecstr& params) {ph();}

void idkwhattocallthisgame(const vecstr& params) {ph();}

////////////////     End Of Command Area     ///////////////
////////////////////////////////////////////////////////////

void interpretCmd(const string& cmd) {
	
	// if user press enter key without typing any command
	if (cmd.empty()) {
		cout<<endl;
		return;
	}
	
	// this is to take multiple word command like 'add 4 2'
	istringstream iss(cmd);
	string maincmd;
	iss >> maincmd;
	
	vecstr params;
	string param;
	while (iss >> param) {
		params.push_back(param);
	}
	
	// command map
	uomap commands = {
		// command area
		{"help", printInAppHelp},
		{"cmds", printInAppHelp},
		{"cmd", printInAppHelp},
		{"ver", printtermver},
		{"version", printtermver},
		{"termver", printtermver},
		{"pwd", pwd},
		{"mkfile", mkfil},
		{"mkdir", mkfol},
		{"cd", cdir},
		{"exit", exitterm},
		{"ls", getDirContent},
		{"clear", cls},
		{"liltool", liltoolent},
		{"psexec", psexec},
		{"cmdinteract", cmdinteract},
		{"mas", masent},
		{"ren", renamef},
		{"game", idkwhattocallthisgame},
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// alias area
		{"pex", psexec},
		{"citr", cmdinteract}//,
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
		// {"", },
	};
	
	if (commands.find(maincmd) != commands.end()) {
		commands[maincmd](params);
	} else {
		cout << maincmd << ": command not found." << endl;
	} //else {
		//quotedOutput("error", "invalid internal command! report this as a bug! [err_invalInterCmd]");
	//}
}

void cmdLoop() {
	while (true) {
		string cmd = getCmd();
		interpretCmd(cmd);
		// cout<<endl;
	}
}

void processArgs(int argc, char* argv[]) {
	// convert 'argv' into string because...
	// IDGAF as chatgpt told me to
	vecstr args(argv, argv + argc);
	string platform = checkPlatform();
	
	// iterate through arguments
	for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--verbose") {
            quotedOutput("debug", "Verbose mode enabled.");
			verbosemode = true;
        } else if (args[i] == "-h" || args[i] == "-H" || args[i] == "--help") {
            printHelp();
			cout << endl;
			printInAppHelp(dummy);
            exit(0);
        } else if (args[i] == "-v" || args[i] == "-V" || args[i] == "--version") {
            printVer();
            exit(0);
        } else if (args[i] == "--osinfo") {
			if (platform == "windows") {
				system("systeminfo");
			} else {
				system("uname -a");
			}
     // } else if (args[i] == "--testcmd") {
			// if (i + 1 < argc) {
				// string cmdtobetest = argv[i + 1];
				// testFunc(cmdtobetest);
				// i++;
			// } else {
				// quotedOutput("error", "\"--testcmd\" requires an argument.");
				// return 1;
			// }
		} else {
            quotedOutput("error", "Unknown argument: " + args[i]);
            exit(1); // Exit with an error, yeah
        }
    }
	// chatgpt says the function ends here
}



// tests and checks...
string testFunc(string func) {
	if (func == "quotedOutput") {
		cout << "testing 'quotedOutput()' function..." << endl;
		cout << "command executed: \"quotedOutput(\"error\", \"This is an error message.\");\"." << endl;
		quotedOutput("error", "This is an error message.");
		cout << "command executed: \"quotedOutput(\"warning\", \"This is a warning message.\");\"." << endl;
		quotedOutput("warning", "This is a warning message.");
		cout << "command executed: \"quotedOutput(\"debug\", \"This is a debug message.\");\"." << endl;
		quotedOutput("debug", "This is a debug message.");
		cout << "command executed: \"quotedOutput(\"info\", \"This is an invalid quote type message.\");\".";
		quotedOutput("info", "This is an invalid quote type message.");
		cout << "end of \"quotedOutput\" function test.\n" << endl;
	} else if (func == "getCmd") {
		cout << "testing \"getCmd\" function...";
		cout << "please input any command/text after the arrow.";
		string cmd = getCmd();
		cout << "received command/text: " << cmd << endl;
		cout << "end of \"getCmd\" function test.";
	} else {
		quotedOutput("error", "No command to test, aborted.");
	}
	return 0;
}


// da main function

int main(int argc, char* argv[]) {
	//why... WHY
	cout << "Initializing..." << endl;
	
	// PROCESS 1 : check for any incomming parameters
	// check for parameters
	// if detected a paarameter, throws it to a function.
	cout << "Checking for parameters..." << endl; sleep(100);
	if (argc > 1) {
		processArgs(argc, argv);
	} else {
		cout << "No parameter/arguments passed, proceed." << endl;
	}
	
	cls(dummy);
	// PROCESS 2 : ALWAYS welcome the user
    cout<<"Welcome to " << "Atmos Terminal - version "<< termver <<endl;
    cout<<"Enter 'help' to get a list of avalible commands."<<endl;
	
	if (verbosemode == true) {quotedOutput("debug", "Verbose mode enabled");}
	if (verbosemode == true){quotedOutput("debug", string("Hostname: ")+getHostname());}
	
	// for nothing? for beauty!
	cout << endl;
	
	// PROCESS 3 : the function!
	// this is the main function of the program...
	// basically: [ username> command ]
	cmdLoop();
	
	// sleep(999999);

    return 0;
}