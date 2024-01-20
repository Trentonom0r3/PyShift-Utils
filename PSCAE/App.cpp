#include "pch.h"
#include "App.h"

Project App::getProject()
{
	Command cmd;
	std::string sessionID = createUUID(); // Generate a new session ID for the Project
	cmd.sessionID = sessionID;
	cmd.name = "getProject";
	cmd.args.push_back(sessionID);

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != sessionID) {
		//this command wasn't for us, ignore until we get the right one
		resp = mqm.receiveResponse();
	}
	std::string projectID = boost::get<std::string>(resp.args[0]);
	Project project(projectID);
	return project;
}


void App::reportInfo(std::string info) { //should modify to accept string, int, float, etc.
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "reportInfo";
	cmd.args.push_back(info);

	// Send the Command
	mqm.sendCommand(cmd);
}

void App::beginUndoGroup(std::string undoName) {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "beginUndoGroup";
	cmd.args.push_back(undoName);

	// Send the Command
	mqm.sendCommand(cmd);

}

void App::endUndoGroup() {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "endUndoGroup";

	// Send the Command
	mqm.sendCommand(cmd);
}

void App::executeCommand(int commandId) {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "executeCommand";
	cmd.args.push_back(commandId);

	// Send the Command
	mqm.sendCommand(cmd);
}

std::string App::pluginPaths() {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getPluginPaths";
	cmd.args.push_back(this->sessionID);
	// Send the Command
	mqm.sendCommand(cmd);

	// Receive the Response
	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//this command wasn't for us, ignore until we get the right one
		resp = mqm.receiveResponse();
	}

	// Return the result
	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}