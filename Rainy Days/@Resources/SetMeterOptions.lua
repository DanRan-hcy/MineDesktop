function Update()
  local barHeight = SKIN:ParseFormula(SKIN:GetVariable("BarHeight"))
  local barWidth, barGap = SKIN:ParseFormula(SKIN:GetVariable("BarWidth")), SKIN:ParseFormula(SKIN:GetVariable("BarGap"))
  local offset = barWidth + barGap
  local color, slant = SKIN:GetVariable("Color"), SKIN:GetVariable("Slant")
  local meterName, lowerLimit, upperLimit = {}, SKIN:ParseFormula(SKIN:GetVariable("FirstBandIndex")) + 1, (SKIN:ParseFormula(SKIN:GetVariable("Bands")) - 1) + 1
  
  for i = lowerLimit, upperLimit do
    meterName[i] = "MeterRotator" .. i-1
	if SKIN:GetMeter(meterName[i]) == nil then return 0 end
    SKIN:Bang("!SetOption", meterName[i], "Group", "Rotators")
    SKIN:Bang("!UpdateMeter", meterName[i])
  end
  
  SKIN:Bang("!SetOptionGroup", "Rotators", "W", barWidth)
  for i = lowerLimit, upperLimit do
    SKIN:Bang("!SetOption", meterName[i], "X", offset * (i - lowerLimit))
  end  
  
  if slant ~= "None" then
  	if slant ~= "Right" then
  	  SKIN:Bang("!SetOptionGroup", "Rotators", "TransformationMatrix", "(Cos(-5*PI/180));(-Sin(-5*PI/180));(Sin(-5*PI/180));(Cos(-5*PI/180));0;0")
  	else
      SKIN:Bang("!SetOptionGroup", "Rotators", "TransformationMatrix", "(Cos(5*PI/180));(-Sin(5*PI/180));(Sin(5*PI/180));(Cos(5*PI/180));0;0")
  	end
  	
  	SKIN:Bang("!SetOptionGroup", "Rotators", "AntiAlias", 1)
    SKIN:Bang("!UpdateMeterGroup", "Rotators")
    SKIN:Bang("!SetOptionGroup", "Rotators", "TransformationMatrix", "")
  end
  
  SKIN:Bang("!SetOptionGroup", "Rotators", "GradientAngle", 90)
  SKIN:Bang("!SetOptionGroup", "Rotators", "SolidColor", color .. ",0")
  SKIN:Bang("!SetOptionGroup", "Rotators", "SolidColor2", color .. ",255")
  
  SKIN:Bang("!SetOptionGroup", "Rotators", "LeftMouseUpAction", "#OpenSettingsWindow#")
  SKIN:Bang("!UpdateMeterGroup", "Rotators")
end