#include "pch.h"
#include "Project.h"



std::shared_ptr<Item> Project::ActiveItem() {
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "ActiveItem";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string ID = resp.sessionID;

	std::string itemIDH = boost::get<std::string>(resp.args[0]);
	std::string type = boost::get<std::string>(resp.args[1]);

	if (type == "Folder") {
		std::shared_ptr<FolderItem> item = std::make_shared<FolderItem>(itemIDH);
		return item;
	}
	else if (type == "Footage") {
		std::shared_ptr<FootageItem> item = std::make_shared<FootageItem>(itemIDH);
		return item;
	}
	else if (type == "Comp") {
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

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string ID = resp.sessionID;


	std::string itemIDH = boost::get<std::string>(resp.args[0]);


	std::shared_ptr<Layer> layer = std::make_shared<Layer>(itemIDH);
	return layer;

}

std::string Project::getName()
{
Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "GetProjectName";

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string ID = resp.sessionID;

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

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string ID = resp.sessionID;

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

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);
}


std::shared_ptr<ProjectCollection> Project::ChildItems()
{
Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getChildItems";

	auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string ID = resp.sessionID;

	std::string itemIDH = boost::get<std::string>(resp.args[0]);

	std::shared_ptr<ProjectCollection> collection = std::make_shared<ProjectCollection>(itemIDH);
	return collection;

}

std::shared_ptr<ProjectCollection> Project::SelectedItems()
{
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getSelectedItems";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string ID = resp.sessionID;

	std::string itemIDH = boost::get<std::string>(resp.args[0]);


	std::shared_ptr<ProjectCollection> collection = std::make_shared<ProjectCollection>(itemID);
	return collection;
}

std::vector<std::shared_ptr<Item>> ProjectCollection::getItems()
{
	try {
		std::vector<std::shared_ptr<Item>> Items;
		Command cmd;
		cmd.name = "getItems";
		cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
		mqm.sendCommand(cmd);

		Response resp;
		while (!mqm.tryReceiveResponse(resp)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		CommandArg arg = resp.args[0];	
		CommandArg arg2 = resp.args[1];
// To check if arg holds std::vector<std::string>
		std::vector<std::string> itemHandles = boost::get<std::vector<std::string>>(arg);
		std::vector<std::string> itemTypes = boost::get<std::vector<std::string>>(arg2);

		for (int i = 0; i < itemHandles.size(); i++) {
			if (itemTypes[i] == "Folder") {
				std::shared_ptr<FolderItem> item = std::make_shared<FolderItem>(itemHandles[i]);
				Items.push_back(item);
			}
			else if (itemTypes[i] == "Footage") {
				std::shared_ptr<FootageItem> item = std::make_shared<FootageItem>(itemHandles[i]);
				Items.push_back(item);
			}
			else if (itemTypes[i] == "Comp") {
				std::shared_ptr<CompItem> item = std::make_shared<CompItem>(itemHandles[i]);
				Items.push_back(item);
			}
			else {
				std::shared_ptr<Item> item = std::make_shared<Item>(itemHandles[i]);
				Items.push_back(item);
			}
		}
		return Items;
	}
	catch (boost::bad_get& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<std::shared_ptr<Item>> ProjectCollection::append(std::shared_ptr<Item> item)
{
	std::vector<std::shared_ptr<Item>> items;
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "appendItem";
	cmd.args.push_back(item->sessionID);
		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string ID = resp.sessionID;


	CommandArg arg = resp.args[0];
	CommandArg arg2 = resp.args[1];
	// To check if arg holds std::vector<std::string>
	if (boost::get<std::vector<std::string>>(&arg) != nullptr) {
		// arg holds a std::vector<std::string>
		std::vector<std::string> itemIDs = boost::get<std::vector<std::string>>(arg);

		if (boost::get<std::vector<std::string>>(&arg2) != nullptr) {
			// arg holds a std::vector<std::string>
			std::vector<std::string> itemTypes = boost::get<std::vector<std::string>>(arg2);
			for (int i = 0; i < itemIDs.size(); i++) {
				std::string itemIDH = itemIDs[i];
				std::string itemType = itemTypes[i];
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
	}
	else {
		// arg holds a std::string
		std::string itemIDH = boost::get<std::string>(arg);
		std::string itemType = boost::get<std::string>(arg2);
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
		return items;
	}
}
