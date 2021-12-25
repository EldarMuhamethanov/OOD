"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ResizeHandler = void 0;
var Signal_1 = require("../common/Signal");
var TagName_1 = require("../common/TagName");
var HANDLER_SIDE_SIZE = 10;
var MIN_WIDTH = 20;
var MIN_HEIGHT = 20;
var ResizeHandler = /** @class */ (function () {
    function ResizeHandler(element) {
        this.onRectChangeSignal = new Signal_1.Signal();
        this.windowMouseMoveHandler = function () { };
        this.windowMouseUpHandler = function () { };
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
        handler.style.pointerEvents = 'all';
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
        window.removeEventListener('mousemove', this.windowMouseMoveHandler);
        window.removeEventListener('mouseup', this.windowMouseUpHandler);
    };
    ResizeHandler.prototype.handlerMouseMove = function (e, type, startRect) {
        var mouseLeft = e.clientX;
        var mouseTop = e.clientY;
        var elementBounds = this.m_element.getBoundingClientRect();
        if (type === "leftTop") {
            var left = Math.min(mouseLeft, startRect.right - MIN_WIDTH);
            var top_1 = Math.min(mouseTop, startRect.bottom - MIN_HEIGHT);
            this.onRectChangeSignal.dispatch({
                left: left,
                top: top_1,
                width: elementBounds.right - left,
                height: elementBounds.bottom - top_1,
            });
        }
        else if (type === "rightTop") {
            var top_2 = Math.min(mouseTop, startRect.bottom - MIN_HEIGHT);
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: top_2,
                width: Math.max(mouseLeft - elementBounds.left, MIN_WIDTH),
                height: elementBounds.bottom - top_2,
            });
        }
        else if (type === "leftBottom") {
            var left = Math.min(mouseLeft, startRect.right - MIN_WIDTH);
            this.onRectChangeSignal.dispatch({
                left: left,
                top: elementBounds.top,
                width: elementBounds.right - left,
                height: Math.max(mouseTop - elementBounds.top, MIN_HEIGHT),
            });
        }
        else if (type === "rightBottom") {
            this.onRectChangeSignal.dispatch({
                left: elementBounds.left,
                top: elementBounds.top,
                width: Math.max(mouseLeft - elementBounds.left, MIN_WIDTH),
                height: Math.max(mouseTop - elementBounds.top, MIN_HEIGHT),
            });
        }
    };
    ResizeHandler.prototype.subscribeOnDnd = function (controller, type) {
        var _this = this;
        controller.onmousedown = function (e) {
            e.preventDefault();
            var elementsBounds = _this.m_element.getBoundingClientRect();
            _this.windowMouseMoveHandler = function (e) { return _this.handlerMouseMove(e, type, {
                left: elementsBounds.left,
                top: elementsBounds.top,
                bottom: elementsBounds.bottom,
                right: elementsBounds.right,
            }); };
            _this.windowMouseUpHandler = function () { return _this.handleMouseUp(); };
            window.addEventListener('mousemove', _this.windowMouseMoveHandler);
            window.addEventListener('mouseup', _this.windowMouseUpHandler);
        };
    };
    ResizeHandler.prototype.addResizeHandlers = function () {
        var leftTopResizeController = document.createElement(TagName_1.TagName.DIV);
        var rightTopResizeController = document.createElement(TagName_1.TagName.DIV);
        var leftBottomResizeController = document.createElement(TagName_1.TagName.DIV);
        var rightBottomResizeController = document.createElement(TagName_1.TagName.DIV);
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