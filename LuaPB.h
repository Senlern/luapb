
#ifndef LUAPB_H_
#define LUAPB_H_

//#include <lua.h>
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <google/protobuf/message.h>
#include <string>

#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>

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

typedef struct tagluamsg
{
	google::protobuf::Message* msg;
	bool isDelete; //是否要释放掉这个msg;
}lua_pbmsg;

typedef struct tagluarepeatedmsg
{
	google::protobuf::Message* msg;
	google::protobuf::FieldDescriptor* field;
}lua_repeated_msg;

#define PB_MESSAGE "pb2"
#define PB_MESSAGE_META "pb_meta"

#define PB_REPEATED_MESSAGE_META "pb_repeated_meta"

extern "C" int luaopen_luapb(lua_State* L);

#endif
