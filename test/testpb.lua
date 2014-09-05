local pb = require("pb");
pb.import("test.proto");

local pbn = 1
function testpb()
	print("***********************************************************")
	print("----pb n: ", pbn);
	pbn = pbn+1

	local msg = pb.new("person.persons");
	msg.uid = 10000+pbn;
	msg.uname = "uname--";
	msg.udescription = "udescription..";
	msg.strs:add("str1");
	msg.strs:add("str2");
	msg.strs:add("str3");
	
	local pInfo
	msg.persons:add();
	pInfo = msg.persons:get(1);
	pInfo.id = 10001
	pInfo.name = "person 001"
	
	msg.persons:add();
	pInfo = msg.persons:get(2);
	pInfo.id = 10002
	pInfo.name = "person 002"
	
	print("uid: " .. msg.uid);
	print("uname: " .. msg.uname);
	print("udescription: " .. msg.udescription);

	for i = 1, msg.strs:len() do
		print("str " .. i .. " : " .. msg.strs:get(i)); 
	end
	
	for i = 1, msg.persons:len() do
		print("id " .. i .. " : " .. msg.persons:get(i).id); 
		print("name " .. i .. " : " .. msg.persons:get(i).name); 
	end

	msg.strs[1] = "after == 11"
	print("===== strs1: " .. msg.strs:get(1))

	msg.strs:set(2, "after set 2")
	print("===== strs2: " .. msg.strs:get(2))

	print("***********************************************************")
	local s = pb.serializeToString(msg)
	local msg2 = pb.new("person.persons");
	pb.parseFromString(msg2, s)
	print("uid: " .. msg2.uid);
	print("uname: " .. msg2.uname);
	print("udescription: " .. msg2.udescription);

	for i = 1, msg2.strs:len() do
		print("str " .. i .. " : " .. msg2.strs:get(i)); 
	end
	
	for i = 1, msg2.persons:len() do
		--local value = msg2.strs:get(i);
		print("id " .. i .. " : " .. msg2.persons:get(i).id); 
		print("name " .. i .. " : " .. msg2.persons:get(i).name); 
	end

	msg2.strs[1] = "after == 110000"
	print("===== strs1: " .. msg2.strs:get(1))

	msg2.strs:set(2, "after set 220000")
	print("===== strs2: " .. msg2.strs:get(2))
	
	print("str: " .. pb.tostring(msg));
	print("***********************************************************")
end

testpb()