支持lua中对protobuf的动态解析

依赖：protobuf 2.5.0/2.4.1，lua。

编译：LuaPB.cc，LuaPB.h加入工程，lua初始化后调用luaopen_luapb(lua_State* L);即可
	  在lua中使用

注意事项：
	lua里设置enum类型的值时，直接使用数值，获取enum值时正常.
	lua里设置bool类型的值时使用数值，0代表false，非0代表true，获取bool的值时正常。
	详情参考代码
  
感谢zhanjunxiong大神的无私分享！
原项目链接： https://github.com/zhanjunxiong/luapb
