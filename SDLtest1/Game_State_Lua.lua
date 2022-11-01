require("Player")

print("Hello from Lua")

p1 = Player:New(2332)

function Initialize()
	print("INITIALIZE!!!")
	cpp_createWindow("hello", 50, 50, 600, 600)
end


function Update()
	print("UPDATE!!")
	print(p1.base.num)
	cpp_luaTest();
end

function Render()
	print("RENDER!!")
end
