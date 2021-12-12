"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeRenderer = void 0;
var ShapeController_1 = require("./ShapeController");
var DragNDropHandler_1 = require("../handlers/DragNDropHandler");
var ResizeHandler_1 = require("../handlers/ResizeHandler");
var Signal_1 = require("../Signal");
var MIN_WIDTH = 20;
var MIN_HEIGHT = 20;
var ShapeRenderer = /** @class */ (function () {
    function ShapeRenderer(model, canvas) {
        var _this = this;
        this.m_element = document.createElement('div');
        this.onSelectSignal = new Signal_1.Signal();
        this.m_model = model;
        this.m_canvas = canvas;
        this.m_controller = new ShapeController_1.ShapeController(model, this);
        this.m_model.getOnRectChange().add(function () { return _this.rerender(); });
    }
    ShapeRenderer.prototype.getOnSelectSignal = function () {
        return this.onSelectSignal;
    };
    Object.defineProperty(ShapeRenderer.prototype, "model", {
        get: function () {
            return this.m_model;
        },
        enumerable: false,
        configurable: true
    });
    ShapeRenderer.prototype.setSelected = function (isSelected) {
        this.m_controller.setIsSelected(isSelected);
    };
    ShapeRenderer.prototype.rerender = function () {
        var left = this.m_model.left;
        var top = this.m_model.top;
        var width = this.m_model.width;
        var height = this.m_model.height;
        this.m_element.style.left = "".concat(left, "px");
        this.m_element.style.top = "".concat(top, "px");
        this.m_element.style.width = "".concat(width, "px");
        this.m_element.style.height = "".concat(height, "px");
        this.m_element.style.position = 'absolute';
        this.m_element.style.boxShadow = this.m_model.isSelected
            ? '0 0 0 2px blue'
            : '';
        var svg = this.m_element.getElementsByTagName('svg')[0];
        if (svg) {
            svg.outerHTML = this.getShapeHtmlImpl();
        }
        else {
            this.m_element.innerHTML = this.getShapeHtmlImpl();
        }
    };
    ShapeRenderer.prototype.handleMove = function (position, canvas) {
        var canvasBounds = canvas.getBoundingClientRect();
        var left = position.left;
        var top = position.top;
        var width = this.m_model.width;
        var height = this.m_model.height;
        this.m_controller.setRect(Math.min(Math.max(left - canvasBounds.left, 0), canvasBounds.right - canvasBounds.left - width), Math.min(Math.max(top - canvasBounds.top, 0), canvasBounds.bottom - canvasBounds.top - height), width, height);
    };
    ShapeRenderer.prototype.handleResize = function (rect, canvas) {
        var canvasBounds = canvas.getBoundingClientRect();
        var left = Math.max(rect.left, canvasBounds.left);
        var top = Math.max(rect.top, canvasBounds.top);
        var right = Math.min(rect.left + rect.width, canvasBounds.right);
        var bottom = Math.min(rect.top + rect.height, canvasBounds.bottom);
        this.m_controller.setRect(left - canvasBounds.left, top - canvasBounds.top, Math.max(right - left, MIN_WIDTH), Math.max(bottom - top, MIN_HEIGHT));
    };
    ShapeRenderer.prototype.render = function () {
        var _this = this;
        this.m_element.innerHTML = '';
        this.rerender();
        var canvasDomElement = this.m_canvas.getDomElement();
        if (this.m_model.isSelected) {
            var resizeHandler = new ResizeHandler_1.ResizeHandler(this.m_element);
            resizeHandler.getOnRectChangeSignal().add(function (rect) { return _this.handleResize(rect, canvasDomElement); });
        }
        var dndHandler = new DragNDropHandler_1.DragNDropHandler(this.m_element);
        dndHandler.getOnMoveSignal().add(function (newPosition) { return _this.handleMove(newPosition, canvasDomElement); });
        dndHandler.getOnDragStart().add(function () { return _this.onSelectSignal.dispatch(); });
        canvasDomElement.appendChild(this.m_element);
    };
    return ShapeRenderer;
}());
exports.ShapeRenderer = ShapeRenderer;
//# sourceMappingURL=ShapeRenderer.js.map