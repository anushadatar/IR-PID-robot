load matlab.mat
for n = 1:length(leftSensor)
    if rightWheel(n) ~= 37
        rightWheel(n) = leftWheel(n);
        leftWheel(n) = leftWheelturn(n);
    end
end
%%
t = [1:length(leftSensor)]*5;
threshold = 950;
figure
clf
subplot(2,1,1)
plot(t,leftSensor)
hold on
plot(t,rightSensor)
line([t(1) t(end)],[threshold threshold],'Color','black','LineStyle','--')
title('Left and Right Sensor Data')
legend('Left Sensor Data', 'Right Sensor Data','Location', 'best','Orientation','horizontal')
ylabel('Magnitude')
xlabel('Time (ms)')
subplot(2,1,2)
plot(t,leftWheel)
hold on
plot(t,rightWheel)
title('Left and Right Wheel Velocities')
ylabel('Magnitude')
xlabel('Time (ms)')
legend('Left Wheel','Right Wheel', 'Location', 'best','Orientation','horizontal')