-- events.lua

function printEvent (evt, time)
    print (string.format("Mouse: (%d, %d)", evt.mousePos.x, evt.mousePos.y))
    print (string.format("Delta: (%d, %d)", evt.mouseDelta.x, evt.mouseDelta.y))
    print (string.format("Button: %d", evt.mouseButton))
    print (string.format("Key:    %04x (%c)", evt.key, evt.key))
    end

function keyDown (evt, time)
    if(evt.key == string.byte('q')) then done = true; end
    Events.keys[evt.key] = true
    end
    
function keyUp (evt, time)
    Events.keys[evt.key] = nil
    end
    
function mouseDown (evt, time)
    Events.clicked = true
    end

function mouseUp (evt, time)
    Events.clicked = false
    end

function mouseMoved (evt, time)
    cursor:moveto(evt.mousePos.x, evt.mousePos.y)
    end
    

Events = {keyDownEvents = keyDown,
          keyUpEvents = keyUp,
          mouseDownEvents = mouseDown,
          mouseUpEvents = mouseUp,
          mouseMovedEvents = mouseMoved,
          keys = {},
          clicked = false}
          
