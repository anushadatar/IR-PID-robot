leftSensorData = linspace(0, 1023);
rightSensorData = linspace(0, 1023);
rightWheel = linspace(0, 1023);
leftWheel = linspace(0, 1023);

for i = leftSensorData
    if i > 950 
        % Turning
        rightWheel(i) = 30;
        leftWheel(i) = -30; 
    else 
        % Go straight
        rightWheel(i) = 30;
        leftWheel(i) = 30;
    end
end 

% Do same thing for right sensor

% Plot with lots of colors - left sensor response and each motor speed
