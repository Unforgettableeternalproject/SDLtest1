Entity = {}
Entity.__index = Entity

function Entity:New(nr)
	local this = {
		num = nr
	}

	setmetatable(this, self)
	return this

end

