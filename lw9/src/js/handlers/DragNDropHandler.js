"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.DragNDropHandler = void 0;
var Signal_1 = require("../Signal");
var DragNDropHandler = /** @class */ (function () {
    function DragNDropHandler(element) {
        var _this = this;
        this.onMoveSignal = new Signal_1.Signal();
        this.onDragStart = new Signal_1.Signal();
        this.m_element = element;
        this.m_element.onmousedown = function (e) {
            if (!e.defaultPrevented) {
                e.preventDefault();
                _this.onDragStart.dispatch();
                _this.onShapeMouseDown(e);
            }
        };
    }
    DragNDropHandler.prototype.getOnDragStart = function () {
        return this.onDragStart;
    };
    DragNDropHandler.prototype.getOnMoveSignal = function () {
        return this.onMoveSignal;
    };
    DragNDropHandler.prototype.onShapeMouseUp = function () {
        window.onmousemove = null;
        window.onmouseup = null;
    };
    DragNDropHandler.prototype.onShapeMove = function (e, leftOffset, topOffset) {
        this.onMoveSignal.dispatch({
            left: e.x - leftOffset,
            top: e.y - topOffset,
        });
    };
    DragNDropHandler.prototype.onShapeMouseDown = function (e) {
        var _this = this;
        var elementBounds = this.m_element.getBoundingClientRect();
        var resultLeftOffset = (e.x - elementBounds.left);
        var resultTopOffset = (e.y - elementBounds.top);
        window.onmousemove = function (e) { return _this.onShapeMove(e, resultLeftOffset, resultTopOffset); };
        window.onmouseup = function () { return _this.onShapeMouseUp(); };
    };
    return DragNDropHandler;
}());
exports.DragNDropHandler = DragNDropHandler;
//# sourceMappingURL=DragNDropHandler.js.map