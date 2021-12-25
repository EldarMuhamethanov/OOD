"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.DragNDropHandler = void 0;
var Signal_1 = require("../common/Signal");
var DragNDropHandler = /** @class */ (function () {
    function DragNDropHandler(element) {
        var _this = this;
        this.onMoveSignal = new Signal_1.Signal();
        this.onShapeMouseDownCallback = function () { };
        this.onShapeMouseMoveCallback = function () { };
        this.onShapeMouseUpCallback = function () { };
        this.m_element = element;
        this.onShapeMouseDownCallback = function (e) { return _this.onShapeMouseDown(e); };
        this.m_element.addEventListener('mousedown', this.onShapeMouseDownCallback);
    }
    DragNDropHandler.prototype.getOnMoveSignal = function () {
        return this.onMoveSignal;
    };
    DragNDropHandler.prototype.onShapeMouseUp = function () {
        window.removeEventListener('mousemove', this.onShapeMouseMoveCallback);
        window.removeEventListener('mouseup', this.onShapeMouseUpCallback);
    };
    DragNDropHandler.prototype.onShapeMove = function (e, leftOffset, topOffset) {
        this.onMoveSignal.dispatch({
            left: e.x - leftOffset,
            top: e.y - topOffset,
        });
    };
    DragNDropHandler.prototype.onShapeMouseDown = function (e) {
        var _this = this;
        if (!e.defaultPrevented) {
            e.preventDefault();
            var elementBounds = this.m_element.getBoundingClientRect();
            var resultLeftOffset_1 = (e.x - elementBounds.left);
            var resultTopOffset_1 = (e.y - elementBounds.top);
            this.onShapeMouseMoveCallback = function (e) { return _this.onShapeMove(e, resultLeftOffset_1, resultTopOffset_1); };
            this.onShapeMouseUpCallback = function () { return _this.onShapeMouseUp(); };
            window.addEventListener('mousemove', this.onShapeMouseMoveCallback);
            window.addEventListener('mouseup', this.onShapeMouseUpCallback);
        }
    };
    return DragNDropHandler;
}());
exports.DragNDropHandler = DragNDropHandler;
//# sourceMappingURL=DragNDropHandler.js.map