#include "../pch.h"
#include "ItemManager.h"

void Item::deleteItem()
{
	Command cmd;
	cmd.name = "DeleteItem";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

std::string Item::getItemHandle()
{
	return this->sessionID;
}


bool Item::isSelected()
{
	Command cmd;
	cmd.name = "IsItemSelected";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	bool output = boost::get<bool>(resp.args[0]);
	return output;
}

void Item::setSelected(bool select)
{
	Command cmd;
	cmd.name = "SelectItem";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(select);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

std::string Item::getName()
{
	Command cmd;
	cmd.name = "GetItemName";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}


void Item::setName(std::string name)
{
	Command cmd;
	cmd.name = "SetItemName";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(name);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

}

float Item::getWidth()
{
	Command cmd;
	cmd.name = "GetItemWidth";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Item::getHeight()
{
	Command cmd;
	cmd.name = "GetItemHeight";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Item::getCurrentTime()
{
	Command cmd;
	cmd.name = "GetItemCurrentTime";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Item::getDuration()
{
	Command cmd;
	cmd.name = "GetItemDuration";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}

void Item::setCurrentTime(float time)
{
	Command cmd;
	cmd.name = "SetItemCurrentTime";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(time);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

float CompItem::getFrameRate()
{
	Command cmd;
	cmd.name = "GetCompFramerate";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}

void CompItem::setFrameRate(float frameRate)
{
	Command cmd;
	cmd.name = "SetCompFramerate";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(frameRate);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

float CompItem::getDuration()
{
	Command cmd;
	cmd.name = "GetCompWorkAreaDuration";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}


void CompItem::setDuration(float duration)
{
	Command cmd;
	cmd.name = "SetCompDuration";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(duration);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

void CompItem::setWidth(float width)
{
	Command cmd;
	cmd.name = "SetCompWidth";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(width);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

void CompItem::setHeight(float height)
{
	Command cmd;
	cmd.name = "SetCompHeight";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(height);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

std::shared_ptr<Layer> CompItem::newSolid(std::string name, float width, float height,float red, float green, float blue, float alpha,
						float duration)
{
	Command cmd;
	cmd.name = "CreateSolidInComp";
	cmd.args.push_back(name);
	cmd.args.push_back(width);
	cmd.args.push_back(height);
	cmd.args.push_back(red);
	cmd.args.push_back(green);
	cmd.args.push_back(blue);
	cmd.args.push_back(alpha);
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(duration);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string layerHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<Layer> layer = std::make_shared<Layer>(layerHandle);
	return layer;
}


std::shared_ptr<LayerCollection> CompItem::getSelectedLayers()
{
	Command cmd;
	cmd.name = "GetSelectedLayers";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string compHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<LayerCollection> layerCollection = std::make_shared<LayerCollection>(compHandle);
	return layerCollection;
}

std::shared_ptr<LayerCollection> CompItem::getLayers()
{
	Command cmd;
	cmd.name = "GetLayers";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string outID = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<LayerCollection> layerCollection = std::make_shared<LayerCollection>(outID);
	return layerCollection;
}

int CompItem::NumLayers()
{
	Command cmd;
	cmd.name = "GetNumLayers";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	int output = boost::get<int>(resp.args[0]);
	return output;
}

float CompItem::getCurrentTime()
{
	Command cmd;
	cmd.name = "GetCompItemCurrentTime";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	float output = boost::get<float>(resp.args[0]);
	return output;
}

void CompItem::setCurrentTime(float time)
{
	Command cmd;
	cmd.name = "SetCompItemCurrentTime";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(time);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

void CompItem::addLayer(std::string name, std::string path, int index)
{
	Command cmd;
	cmd.name = "AddLayerToComp";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(name);
	cmd.args.push_back(path);
	cmd.args.push_back(index);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

std::string Layer::GetLayerName()
{
Command cmd;
	cmd.name = "GetLayerName";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}

std::string Layer::GetSourceName()
{
	Command cmd;
	cmd.name = "GetLayerSourceName";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}


void Layer::SetLayerName(std::string name)
{
	Command cmd;
	cmd.name = "SetLayerName";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(name);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

int Layer::index()
{
	Command cmd;
	cmd.name = "GetLayerIndex";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	int output = boost::get<int>(resp.args[0]);
	return output;
}

void Layer::changeIndex(int index)
{
	Command cmd;
	cmd.name = "ChangeLayerIndex";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(index);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

std::shared_ptr<FootageItem> Layer::duplicate()
{
	Command cmd;
	cmd.name = "DuplicateLayer";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(output);
	return footageItem;
}

float Layer::layerTime()
{
	Command cmd;
	cmd.name = "GetLayerCurrentTime";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}



float Layer::layerCompTime()
{
Command cmd;
	cmd.name = "GetLayerCurrentTime";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}



float Layer::inPoint()
{	
	Command cmd;
	cmd.name = "GetLayerInPoint";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Layer::compInPoint()
{
	Command cmd;
	cmd.name = "GetLayerInPoint";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Layer::duration()
{
	Command cmd;
	cmd.name = "GetLayerDuration";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Layer::compDuration()
{
	Command cmd;
	cmd.name = "GetLayerDuration";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}


std::string Layer::getQuality()
{
	Command cmd;
	cmd.name = "GetLayerQuality";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}


void Layer::setQuality(int quality)
{
	Command cmd;
	cmd.name = "SetLayerQuality";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(quality);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}


void Layer::deleteLayer()
{
	Command cmd;
	cmd.name = "DeleteLayer";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

float Layer::getOffset()
{
	Command cmd;
	cmd.name = "GetLayerOffset";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	float output = boost::get<float>(resp.args[0]);
	return output;
}

void Layer::setOffset(float offset)
{
	Command cmd;
	cmd.name = "SetLayerOffset";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(offset);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

void Layer::setFlag(LayerFlag flag, bool value)
{
	Command cmd;
	cmd.name = "SetLayerFlag";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(flag);
	cmd.args.push_back(value);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}

bool Layer::getFlag(LayerFlag flag)
{
	Command cmd;
	cmd.name = "GetLayerFlag";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(flag);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	bool output = boost::get<bool>(resp.args[0]);
	return output;
}


std::string Layer::getLayerSessionID()
{
return this->sessionID;
}

std::shared_ptr<Item> Layer::getSource()
{
	Command cmd;
	cmd.name = "GetLayerSource";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<Item> item = std::make_shared<Item>(output);
	return item;
}

std::shared_ptr<ItemCollection> FolderItem::ChildItems()
{
	Command cmd;
	cmd.name = "GetChildItems";
	std::string itemID = createUUID();
	cmd.args.push_back(itemID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();
	std::string ID = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<ItemCollection> itemCollection = std::make_shared<ItemCollection>(ID);
	return itemCollection;
}

void LayerCollection::removeLayerFromCollection(Layer layerHandle)
{
	Command cmd;
	cmd.name = "RemoveLayerFromCollection";
	cmd.sessionID = this->compHandle_;
	cmd.args.push_back(layerHandle.getLayerSessionID());

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

}

void LayerCollection::RemoveLayerByIndex(int index)
{
	Command cmd;
	cmd.name = "RemoveLayerByIndex";
	cmd.sessionID = this->compHandle_;
	cmd.args.push_back(index);

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

}

std::string LayerCollection::getCompName()
{
	Command cmd;
	cmd.name = "GetCompName";
	cmd.sessionID = this->compHandle_;

	MessageQueueManager mqm;

	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}

std::shared_ptr<Layer> LayerCollection::addLayerToCollection(Item itemHandle, int index) {
	Command cmd;
	cmd.name = "AddLayerToCollection";
	cmd.sessionID = this->compHandle_;
	cmd.args.push_back(itemHandle.getItemHandle());
	cmd.args.push_back(index);

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<Layer> layer = std::make_shared<Layer>(output);
	return layer;
}

std::vector<std::shared_ptr<Item>> ItemCollection::getItems()
{
	std::vector<std::shared_ptr<Item>> items;
	Command cmd;
	cmd.name = "GetItems";

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::vector<std::string> itemHandles = boost::get<std::vector<std::string>>(resp.args[0]);
	std::vector<std::string> itemTypes = boost::get<std::vector<std::string>>(resp.args[1]);

	for (int i = 0; i < itemHandles.size(); i++) {
		if (itemTypes[i] == "Folder") {
			std::shared_ptr<FolderItem> folderItem = std::make_shared<FolderItem>(itemHandles[i]);
			items.push_back(folderItem);
		}
		else if (itemTypes[i] == "Footage") {
			std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(itemHandles[i]);
			items.push_back(footageItem);
		}
		else if (itemTypes[i] == "Comp") {
			std::shared_ptr<CompItem> compItem = std::make_shared<CompItem>(itemHandles[i]);
			items.push_back(compItem);
		}
	return items;
}


std::string FootageItem::getPath()
{
	Command cmd;
	cmd.name = "GetFootagePath";
	cmd.args.push_back(this->sessionID);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);

	Response resp = mqm.receiveResponse();

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}

void FootageItem::replaceWithNewSource(std::string name, std::string path)
{
	Command cmd;
	cmd.name = "ReplaceFootage";
	cmd.args.push_back(this->sessionID);
	cmd.args.push_back(name);
	cmd.args.push_back(path);
	cmd.sessionID = this->sessionID;

	MessageQueueManager mqm;
	mqm.sendCommand(cmd);
}
