three_sixty_this_element = function(image, images) {
    var currentIndex = 0;
    var numImages = images.length;
    var startX = 0;
    var rotationDistance = image.parent().width() * 1.6;
    var inProgress = false;
    var currentVelocity = 0;
    var timeOfLastUpdate = 0;
    var frictionPercentage = 0.95;
    var friction = 0.9;
    var timeout;
    
    var startHandler = function(x) {
        // cancel timeout
        if (timeout) { clearTimeout(timeout); timeout = undefined; }
        inProgress = true;
        startX = x;
        return false;
    };

    var moveHandler = function(currentX) {
        if (!inProgress) { return true; }
        
        updateImage(startX - currentX);

        startX = currentX;
        timeOfLastUpdate = new Date().getTime();
        return false;
    };

    var endHandler = function() {
        inProgress = false;
        if (Math.abs(new Date().getTime() - timeOfLastUpdate) < 100) {
            timeout = setTimeout(function() { updateImage(currentVelocity); }, 10);
        } else {
            updateImage(0);
        }
        return false;
    };

    var updateImage = function (newVelocity) {
        currentVelocity = newVelocity;
        currentIndex += currentVelocity / rotationDistance * numImages;

        // Javascript % can return negative values, so make sure that we are in the [0..n] range
        currentIndex = ((currentIndex % numImages) + numImages) % numImages;

        image.attr("src", images[Math.floor(currentIndex)].src);

        if (!inProgress && Math.abs(currentVelocity) > friction) {
            if (currentVelocity > 0) {
                currentVelocity = currentVelocity * frictionPercentage - friction;
            } else {
                currentVelocity = currentVelocity * frictionPercentage + friction;
            }
            timeout = setTimeout(function() { updateImage(currentVelocity); }, 40);
        }
    }

    image.bind("touchstart", function(e) { return startHandler(e.originalEvent.touches[0].pageX); });
    image.bind("mousedown", function(e) { return startHandler(e.originalEvent.pageX); });

    image.bind("touchmove", function(e) { return moveHandler(e.originalEvent.touches[0].pageX); });
    image.bind("mousemove", function(e) { return moveHandler(e.originalEvent.pageX); });

    image.bind("touchend", endHandler);
    image.bind("mouseup", endHandler);
};
