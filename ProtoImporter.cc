#include "ProtoImporter.h"
#include "platform/CCFileUtils.h"

#include <stdio.h>

class MyMultiFileErrorCollector : public google::protobuf::compiler::MultiFileErrorCollector
{
        virtual void AddError(
                const std::string & filename,
                int line,
                int column,
                const std::string & message)
        {
        	fprintf(stderr, "%s:%d:%d:%s\n", filename.c_str(), line, column, message.c_str());
       }
};

static MyMultiFileErrorCollector errorCollector;
static google::protobuf::compiler::DiskSourceTree sourceTree;

static ProtoImporter pProtoImporter;
ProtoImporter &ProtoImporter::instance()
{
	return pProtoImporter;
}

ProtoImporter::ProtoImporter():
		importer(&sourceTree, &errorCollector)
{
	auto fileUtils = cocos2d::FileUtils::getInstance();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		auto path = fileUtils->fullPathForFilename("src/main.lua");
		auto pos = path.find("src/main.lua");
		path.erase(pos);
		path += "res/proto";
		sourceTree.MapPath("", path);
	}
#else
	{
		auto writePath = fileUtils->getWritablePath();
		if(writePath.at(writePath.length()-1) == '\\' || writePath.at(writePath.length()-1) == '/')
		{
			writePath.erase(writePath.length()-1);
		}
 
		sourceTree.MapPath("", writePath + "/res/proto");
	}
#endif

	//printf("[ProtoImporter] protopath:%s\n", protopath);
}

bool ProtoImporter::Import(const std::string& filename)
{
	const  google::protobuf::FileDescriptor* filedescriptor = importer.Import(filename);
	 if (!filedescriptor)
	 {
		 fprintf(stderr, "import (%s) file descriptor error\n", filename.c_str());
		 return false;
	 }
	 return true;
}

google::protobuf::Message* ProtoImporter::createDynamicMessage(const std::string& typeName)
{
	  google::protobuf::Message* message = NULL;
	  const google::protobuf::Descriptor* descriptor = importer.pool()->FindMessageTypeByName(typeName);
	  if (descriptor)
	  {
	     const google::protobuf::Message* prototype = factory.GetPrototype(descriptor);
			if (prototype)
			{
				message = prototype->New();
			}
	  }
	  return message;
}
