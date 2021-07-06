/**
 一个实现滑动门效果的函数
 */

function slidedoor (elements, expose) {
    init();

    for (var i = 0; i < elements.length; i++) {
        (function (i) {
            elements[i].onmouseover = function () {
                setInitPos();
                for (var j = 1; j <= i; j++) {
                    elements[j].style.left = elements[j].offsetLeft - (eleWidth - expose) + 'px';
                }
            }
        })(i);
    }

    function init () {
        var parent = elements[0].parentElement,
            length = elements.length,
            eleWidth = elements[0].offsetWidth;
        parent.style.position = 'relative';
        parent.style.width = eleWidth + (length - 1) * expose + 'px';
        parent.style.overflow = 'hidden';
        parent.style.height = elements[0].offsetHeight + 'px';
        for (var i = 0; i < length; i++) {
            var style = elements[i].style;
            style.position = 'absolute';
            style.display = 'block';
            style.left = 0;
            style.top = 0;
            style.border = '1px solid #ccc';
        }

        setInitPos();
    }

    function setInitPos () {
        for (var i = 1; i < elements.length; i++) {
            elements[i].style.left = elements[0].offsetWidth + (i - 1) * expose + 'px';
        }
    }
}