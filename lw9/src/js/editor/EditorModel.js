"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.EditorModel = void 0;
var Signal_1 = require("../Signal");
var EditorModel = /** @class */ (function () {
    function EditorModel() {
        this.m_shapes = [];
        this.m_selectedShape = null;
        this.m_onSelectedShapeChanged = new Signal_1.Signal();
        this.m_onShapeCreated = new Signal_1.Signal();
        this.m_onShapeRemoved = new Signal_1.Signal();
    }
    EditorModel.prototype.getOnShapeCreated = function () {
        return this.m_onShapeCreated;
    };
    EditorModel.prototype.getOnShapeRemoved = function () {
        return this.m_onShapeRemoved;
    };
    EditorModel.prototype.getOnSelectedShapeChanged = function () {
        return this.m_onSelectedShapeChanged;
    };
    EditorModel.prototype.getSelectedShape = function () {
        return this.m_selectedShape;
    };
    EditorModel.prototype.getShapes = function () {
        return this.m_shapes;
    };
    EditorModel.prototype.setSelectedShape = function (shapeId) {
        if (shapeId !== this.m_selectedShape) {
            this.m_selectedShape = shapeId;
            this.m_onSelectedShapeChanged.dispatch();
        }
    };
    EditorModel.prototype.addShape = function (shape) {
        this.m_shapes.push(shape);
        this.m_onShapeCreated.dispatch(shape);
    };
    EditorModel.prototype.removeSelectedShape = function () {
        var _this = this;
        if (this.m_selectedShape) {
            this.m_shapes = this.m_shapes.filter(function (shape) { return _this.m_selectedShape !== shape.id; });
            var currentSelectedShape = this.m_selectedShape;
            this.m_selectedShape = null;
            this.m_onSelectedShapeChanged.dispatch();
            this.m_onShapeRemoved.dispatch(currentSelectedShape);
        }
    };
    return EditorModel;
}());
exports.EditorModel = EditorModel;
//# sourceMappingURL=EditorModel.js.map