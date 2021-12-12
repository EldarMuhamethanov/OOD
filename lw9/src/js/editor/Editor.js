"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Editor = void 0;
var ToolbarRenderer_1 = require("./ToolbarRenderer");
var Canvas_1 = require("../Canvas/Canvas");
var ShapeFactory_1 = require("../Factory/ShapeFactory");
var generateUid_1 = require("../common/generateUid");
var Editor = /** @class */ (function () {
    function Editor() {
        var _this = this;
        this.m_shapes = [];
        this.m_selectedShape = null;
        this.m_workspace = document.createElement('div');
        this.editorHTML = document.createElement('div');
        this.m_canvas = new Canvas_1.Canvas();
        this.m_canvas.getOnCanvasClick().add(function () { return _this.resetSelectedShape(); });
        this.m_toolbarRenderer = new ToolbarRenderer_1.ToolbarRenderer();
        this.m_toolbarRenderer.getOnCreateShapeSignal().add(function (shapeType) {
            _this.addShape({
                id: (0, generateUid_1.generateUid)(),
                renderer: ShapeFactory_1.ShapeFactory.createShape(shapeType, _this.m_canvas)
            });
            _this.render();
        });
        this.m_toolbarRenderer.getOnDeleteShapeSignal().add(function () {
            if (_this.m_selectedShape) {
                _this.removeShape(_this.m_selectedShape);
                _this.render();
            }
        });
        window.onkeydown = function (e) {
            if (e.key === 'Delete') {
                if (_this.m_selectedShape) {
                    _this.removeShape(_this.m_selectedShape);
                    _this.render();
                }
            }
        };
    }
    Editor.prototype.resetSelectedShape = function () {
        var _this = this;
        if (this.m_selectedShape) {
            var currentSelectedShape = this.m_shapes.find(function (shape) { return shape.id === _this.m_selectedShape; });
            if (currentSelectedShape) {
                currentSelectedShape.renderer.setSelected(false);
            }
            this.m_selectedShape = null;
            this.render();
        }
    };
    Editor.prototype.selectShape = function (shapeId) {
        var _this = this;
        if (this.m_selectedShape !== shapeId) {
            var currentSelectedShape = this.m_shapes.find(function (shape) { return shape.id === _this.m_selectedShape; });
            var newSelectedShape = this.m_shapes.find(function (shape) { return shape.id === shapeId; });
            if (currentSelectedShape) {
                currentSelectedShape.renderer.setSelected(false);
            }
            if (newSelectedShape) {
                newSelectedShape.renderer.setSelected(true);
            }
            this.m_selectedShape = shapeId;
            if (shapeId) {
                this.placeShapeOnFront(shapeId);
            }
            this.render();
        }
    };
    Editor.prototype.addShape = function (shape) {
        var _this = this;
        this.m_shapes.push(shape);
        shape.renderer.getOnSelectSignal().add(function () { return _this.selectShape(shape.id); });
    };
    Editor.prototype.removeShape = function (id) {
        this.m_shapes = this.m_shapes.filter(function (shape) { return shape.id !== id; });
        this.resetSelectedShape();
    };
    Editor.prototype.placeShapeOnFront = function (id) {
        var shape = this.m_shapes.find(function (shape) { return shape.id === id; });
        if (shape) {
            this.m_shapes = this.m_shapes.filter(function (shape) { return shape.id !== id; });
            this.m_shapes.push(shape);
        }
    };
    Editor.prototype.render = function () {
        this.editorHTML.innerHTML = '';
        this.editorHTML.classList.add('main-container');
        this.m_toolbarRenderer.render(this.editorHTML);
        this.m_workspace.classList.add('workspace');
        this.m_canvas.render(this.m_workspace);
        this.editorHTML.appendChild(this.m_workspace);
        document.body.appendChild(this.editorHTML);
        this.m_shapes.forEach(function (shape) { return shape.renderer.render(); });
    };
    return Editor;
}());
exports.Editor = Editor;
//# sourceMappingURL=Editor.js.map