"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.EditorRenderer = void 0;
var Canvas_1 = require("../Canvas/Canvas");
var ToolbarRenderer_1 = require("./ToolbarRenderer");
var ShapeFactory_1 = require("../Factory/ShapeFactory");
var EditorController_1 = require("./EditorController");
var EditorRenderer = /** @class */ (function () {
    function EditorRenderer(model) {
        var _this = this;
        this.m_shapeIdToRendererMap = new Map();
        this.editorHTML = document.createElement('div');
        this.m_model = model;
        this.m_controller = new EditorController_1.EditorController(model, this);
        this.m_model.getOnShapeCreated().add(function (shape) {
            var renderer = ShapeFactory_1.ShapeFactory.createShapeRenderer(shape, _this.m_canvas);
            renderer.getOnSelectSignal().add(function () { return _this.m_controller.setSelectedShape(shape.id); });
            _this.m_shapeIdToRendererMap.set(shape.id, renderer);
            _this.render();
        });
        this.m_model.getOnShapeRemoved().add(function (shapeId) {
            _this.m_shapeIdToRendererMap.delete(shapeId);
            _this.render();
        });
        this.m_model.getOnSelectedShapeChanged().add(function () { return _this.render(); });
        this.m_canvas = new Canvas_1.Canvas();
        this.m_canvas.getOnCanvasClick().add(function () { return _this.m_controller.setSelectedShape(null); });
        this.m_toolbarRenderer = new ToolbarRenderer_1.ToolbarRenderer();
        this.m_toolbarRenderer.getOnCreateShapeSignal().add(function (shapeType) {
            _this.addShape(ShapeFactory_1.ShapeFactory.createShapeModel(shapeType, _this.m_canvas));
        });
        this.m_toolbarRenderer.getOnDeleteShapeSignal().add(function () { return _this.removeShape(); });
        window.onkeydown = function (e) {
            if (e.key === 'Delete') {
                _this.removeShape();
            }
        };
    }
    EditorRenderer.prototype.addShape = function (shapeModel) {
        this.m_controller.addShape(shapeModel);
    };
    EditorRenderer.prototype.removeShape = function () {
        this.m_controller.removeSelectedShape();
    };
    EditorRenderer.prototype.render = function () {
        var _this = this;
        this.editorHTML.innerHTML = '';
        this.editorHTML.classList.add('main-container');
        this.m_toolbarRenderer.render(this.editorHTML);
        var workspace = document.createElement('div');
        workspace.classList.add('workspace');
        this.m_canvas.render(workspace);
        this.editorHTML.appendChild(workspace);
        document.body.appendChild(this.editorHTML);
        this.m_model.getShapes().forEach(function (shape) {
            var shapeId = shape.id;
            var shapeRenderer = _this.m_shapeIdToRendererMap.get(shapeId);
            if (shapeRenderer) {
                shapeRenderer.setSelected(shapeId === _this.m_model.getSelectedShape());
                shapeRenderer.render();
            }
        });
    };
    return EditorRenderer;
}());
exports.EditorRenderer = EditorRenderer;
//# sourceMappingURL=EditorRenderer.js.map