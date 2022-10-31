require("Entity")

Player = {}
Player.__index = Player

function Player:New(nr)
	local this = {
		base = Entity:New(nr)
	}

	setmetatable(this, self)
	return this

end

