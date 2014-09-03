local pb = require("pb");
pb.import("test.proto");

local pbn = 1
function testpb()
	print("----pb n: ", pbn);
	pbn = pbn+1

	local person = pb.new("person.persons");
	person.uid = 10000;
	person.uname = "usersname";
	person.udescription = "random description ~";
	
	person.strs.add("str00001")
	person.strs.add("str00002")
	local p1 = pb.new("person.personInfo");
	p1.id = 10001
	p1.name = "person_001"
	person.persons.add(p1)
	person.persons[1].id = 10001;
	person.persons[1].name = "person_001";
	
	person.persons.add()
	person.persons[2].id = 10002;
	person.persons[2].name = "person_002";

	local ss = pb.serializeToString(person)
	
	local per = pb.new("person.persons");
	pb.parseFromString(per, ss)
	print("uid: " .. per.uid);
	print("param: " .. per.uname);
	print("param1: " .. per.udescription);
	for i = 1, per.strs.len() do
		print(".. : " .. i .. " str: " .. per.strs[i]); 
	end
	for i = 1, per.persons.len() do
		print(".. i: " .. i .. " id: " .. per.persons[i].id .. " name: " .. per.persons[i].name); 
	end
end

testpb()