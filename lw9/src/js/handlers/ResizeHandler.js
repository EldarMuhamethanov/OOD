"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ResizeHandler = void 0;
var Signal_1 = require("../Signal");
var HANDLER_SIDE_SIZE = 10;
var ResizeHandler = /** @class */ (function () {
    function ResizeHandler(element) {
        this.onRectChangeSignal = new Signal_1.Signal();
        this.m_element = element;
        this.addResizeHandlers();
    }
    ResizeHandler.prototype.getOnRectChangeSignal = function () {
        return this.onRectChangeSignal;
    };
    ResizeHandler.prototype.customizeControllers = function (handler, handlerType) {
        handler.style.width = "".concat(HANDLER_SIDE_SIZE, "px");
        handler.style.height = "".concat(HANDLER_SIDE_SIZE, "px");
        handler.style.position = 'absolute';
        handler.style.background = 'blue';
        var offset = "-".concat(HANDLER_SIDE_SIZE / 2, "px");
        if (handlerType === 'leftBottom') {
            handler.style.bottom = offset;
            handler.style.left = offset;
        }
        else if (handlerType === 'leftTop') {
            handler.style.top = offset;
            handler.style.left = offset;
        }
        else if (handlerType === 'rightBottom') {
            handler.style.bottom = offset;
            handler.style.right = offset;
        }
        else if (handlerType === 'rightTop') {
            handler.style.top = offset;
            handler.style.right = offset;
        }
        this.subscribeOnDnd(handler, handlerType);
    };
    ResizeHandler.prototype.handleMouseUp = function () {
        window.onmousemove = null;
        window.onmouseup = null;
    };
    ResizeHandler.prototype.handlerMouseMove = function (e, type) {
        var mouseLeft = e.clientX;
        var mouseTop = e.clientY;
        var elementBounds = this.m_element.getBoundingClientRect();
        if (type === "leftTop") {
            this.onRectChangeSignal.dispatch({
                left: mouseLeft,
                top: mouseTop,
                width: elementBounds.right - mouseLeft,
                height: elementBounds.bottom - mouseTop,
            });
        }
        else if (type === "rightTop") {
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: mouseTop,
                width: mouseLeft - elementBounds.left,
                height: elementBounds.bottom - mouseTop,
            });
        }
        else if (type === "leftBottom") {
            this.onRectChangeSignal.dispatch({
                left: mouseLeft,
                top: elementBounds.top,
                width: elementBounds.right - mouseLeft,
                height: mouseTop - elementBounds.top,
            });
        }
        else if (type === "rightBottom") {
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: elementBounds.top,
                width: mouseLeft - elementBounds.left,
                height: mouseTop - elementBounds.top,
            });
        }
    };
    ResizeHandler.prototype.subscribeOnDnd = function (controller, type) {
        var _this = this;
        controller.onmousedown = function (e) {
            e.preventDefault();
            window.onmousemove = function (e) { return _this.handlerMouseMove(e, type); };
            window.onmouseup = function () { return _this.handleMouseUp(); };
        };
    };
    ResizeHandler.prototype.addResizeHandlers = function () {
        var leftTopResizeController = document.createElement('div');
        var rightTopResizeController = document.createElement('div');
        var leftBottomResizeController = document.createElement('div');
        var rightBottomResizeController = document.createElement('div');
        this.customizeControllers(leftTopResizeController, 'leftTop');
        this.customizeControllers(rightTopResizeController, 'rightTop');
        this.customizeControllers(leftBottomResizeController, 'leftBottom');
        this.customizeControllers(rightBottomResizeController, 'rightBottom');
        this.m_element.appendChild(leftTopResizeController);
        this.m_element.appendChild(rightTopResizeController);
        this.m_element.appendChild(leftBottomResizeController);
        this.m_element.appendChild(rightBottomResizeController);
    };
    return ResizeHandler;
}());
exports.ResizeHandler = ResizeHandler;
//# sourceMappingURL=ResizeHandler.js.map