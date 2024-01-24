#include "../pch.h"
#include "Project.h"


std::shared_ptr<Item> Project::ActiveItem() {
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "ActiveItem";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);
	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::string itemIDH = boost::get<std::string>(resp.args[0]);
	std::string type = boost::get<std::string>(resp.args[1]);
	if (itemIDH != itemID) {
		resp = mqm.receiveResponse();
	}
	if (type == "FolderItem") {
		std::shared_ptr<FolderItem> item = std::make_shared<FolderItem>(itemIDH);
		return item;
	}
	else if (type == "FootageItem") {
		std::shared_ptr<FootageItem> item = std::make_shared<FootageItem>(itemIDH);
		return item;
	}
	else if (type == "CompItem") {
		std::shared_ptr<CompItem> item = std::make_shared<CompItem>(itemIDH);
		return item;
	}
	else {
		std::shared_ptr<Item> item = std::make_shared<Item>(itemIDH);
		return item;
	}
}

std::shared_ptr<Layer> Project::GetActiveLayer()
{
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "GetActiveLayer";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);
	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::string itemIDH = boost::get<std::string>(resp.args[0]);

	if (itemIDH != itemID) {
		resp = mqm.receiveResponse();
	}

	std::shared_ptr<Layer> layer = std::make_shared<Layer>(itemIDH);
	return layer;

}

std::string Project::getName()
{
Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "GetProjectName";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);
	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::string name = boost::get<std::string>(resp.args[0]);

	return name;
}

std::string Project::getPath()
{
Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "GetProjectPath";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);
	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::string path = boost::get<std::string>(resp.args[0]);

	return path;
}

void Project::saveAs(std::string path)
{
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "SaveProjectAs";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);
	cmd.args.push_back(path);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);
}


std::shared_ptr<ProjectCollection> Project::ChildItems()
{
Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getChildItems";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);
	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::string itemIDH = boost::get<std::string>(resp.args[0]);

	if (itemIDH != itemID) {
		resp = mqm.receiveResponse();
	}

	std::shared_ptr<ProjectCollection> collection = std::make_shared<ProjectCollection>(itemID);
	return collection;

}

std::shared_ptr<ProjectCollection> Project::SelectedItems()
{
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getSelectedItems";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::string itemIDH = boost::get<std::string>(resp.args[0]);

	if (itemIDH != itemID) {
		resp = mqm.receiveResponse();
	}

	std::shared_ptr<ProjectCollection> collection = std::make_shared<ProjectCollection>(itemID);
	return collection;
}

std::vector<std::shared_ptr<Item>> ProjectCollection::getItems()
{
	std::vector<std::shared_ptr<Item>> items;
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getItems";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string ID = resp.sessionID;
	if (ID != this->sessionID) {
		//message wasn't for this session, put it back in the queue
		resp = mqm.receiveResponse();
	}

	std::vector<std::string> itemIDs = boost::get<std::vector<std::string>>(resp.args[0]);


	for (int i = 0; i < itemIDs.size(); i++) {
		std::string itemIDH = itemIDs[i];
		std::string itemType = boost::get<std::string>(resp.args[1]);
		if (itemType == "FolderItem") {
			std::shared_ptr<FolderItem> item = std::make_shared<FolderItem>(itemIDH);
			items.push_back(item);
		}
		else if (itemType == "FootageItem") {
			std::shared_ptr<FootageItem> item = std::make_shared<FootageItem>(itemIDH);
			items.push_back(item);
		}
		else if (itemType == "CompItem") {
			std::shared_ptr<CompItem> item = std::make_shared<CompItem>(itemIDH);
			items.push_back(item);
		}
		else {
			std::shared_ptr<Item> item = std::make_shared<Item>(itemIDH);
			items.push_back(item);
		}
	}

	return items;
}
