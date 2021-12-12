"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Canvas = void 0;
var Signal_1 = require("../Signal");
var CANVAS_WIDTH = 640;
var CANVAS_HEIGHT = 480;
var Canvas = /** @class */ (function () {
    function Canvas() {
        this.m_elementHTML = document.createElement('div');
        this.m_width = CANVAS_WIDTH;
        this.m_height = CANVAS_HEIGHT;
        this.onCanvasClick = new Signal_1.Signal();
    }
    Canvas.prototype.getOnCanvasClick = function () {
        return this.onCanvasClick;
    };
    Canvas.prototype.getDomElement = function () {
        return this.m_elementHTML;
    };
    Canvas.prototype.getWidth = function () {
        return this.m_width;
    };
    Canvas.prototype.getHeight = function () {
        return this.m_height;
    };
    Canvas.prototype.render = function (parentElement) {
        var _this = this;
        this.m_elementHTML.innerHTML = '';
        this.m_elementHTML.classList.add('canvas');
        this.m_elementHTML.style.width = "".concat(this.m_width, "px");
        this.m_elementHTML.style.height = "".concat(this.m_height, "px");
        this.m_elementHTML.onmousedown = function (e) {
            if (!e.defaultPrevented) {
                _this.onCanvasClick.dispatch();
            }
        };
        parentElement.appendChild(this.m_elementHTML);
    };
    return Canvas;
}());
exports.Canvas = Canvas;
//# sourceMappingURL=Canvas.js.map