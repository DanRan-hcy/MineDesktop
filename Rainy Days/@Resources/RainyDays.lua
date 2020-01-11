-- RainyDays v2.0
-- LICENSE: Creative Commons Attribution-Non-Commercial-Share Alike 3.0

local measure, meter, heightLookup, positionY = {}, {}, {}, {}

function Initialize()
  floor = math.floor
  multiplier, constant = SELF:GetNumberOption("Multiplier"), SELF:GetNumberOption("Constant")
  cover, meterHeight = floor(SELF:GetNumberOption("Cover") + 0.5), SELF:GetNumberOption("MeterHeight")
  lowerLimit, upperLimit = SELF:GetNumberOption("LowerLimit") + 1, SELF:GetNumberOption("UpperLimit") + 1
  
  rainDivider = floor(cover * 0.5 + 0.5)
  for i = 0, rainDivider do heightLookup[i] = meterHeight * (i / rainDivider) end
  
  for i = lowerLimit, upperLimit do
    measure[i], meter[i] = SKIN:GetMeasure(SELF:GetOption("MeasureBaseName") .. i-1), SKIN:GetMeter(SELF:GetOption("MeterBaseName") .. i-1)
	positionY[i] = math.random(0, cover)
  end
end

function Update()
  for i = lowerLimit, upperLimit do
  
    positionY[i] = (positionY[i] + multiplier * measure[i]:GetValue() + constant) % cover
	
	local positionY = floor(positionY[i] + 0.5)
    
    if positionY <= rainDivider then
	  meter[i]:SetH(heightLookup[positionY])
	else
	  meter[i]:SetH(meterHeight - heightLookup[positionY - rainDivider])
	end
    
	meter[i]:SetY(positionY)
  end
end