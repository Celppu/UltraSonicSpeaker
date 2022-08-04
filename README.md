# UltraSonicSpeaker
 Parametric ultrasonic speaker with arduino and arduino clone.
 
Parametric speakers usually are done with analog circuits or faster micros, but I decided to make low cost and
easier to document version with arduino. Obviously arduino suffers from low bit depth in adc or timer, that is audible in
end generated ultrasound. Clone lgt8f has better adc and faster clock which helps a bit.



#TODO add design. Design currently simple h bridge driving ultrasonic array
Current design
<img src="https://user-images.githubusercontent.com/42336725/182957348-fc9d1d6a-fdab-4a61-8671-5a9a9aeca37b.jpg" width = "50%"/>

Mildly infuriating to realise that elements have random orientation causing 180degree phase shifts. Cant trust orietation of the part itself.
![20220524_132412](https://user-images.githubusercontent.com/42336725/182957507-2fc337aa-afe5-40f4-b572-01983e765363.jpg)
