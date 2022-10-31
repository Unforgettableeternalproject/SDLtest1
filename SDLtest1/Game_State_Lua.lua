require("Player")

print("Hello from Lua")

p1 = Player:New(2332)

function Update()
	print("UPDATE!!")
	print(p1.base.num)
end

function Render()
	print("RENDER!!")
end

a = 100