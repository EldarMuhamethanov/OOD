"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.EditorController = void 0;
var EditorController = /** @class */ (function () {
    function EditorController(model, renderer) {
        this.m_model = model;
        this.m_renderer = renderer;
    }
    EditorController.prototype.addShape = function (shape) {
        this.m_model.addShape(shape);
    };
    EditorController.prototype.removeSelectedShape = function () {
        this.m_model.removeSelectedShape();
    };
    EditorController.prototype.setSelectedShape = function (shapeId) {
        this.m_model.setSelectedShape(shapeId);
    };
    return EditorController;
}());
exports.EditorController = EditorController;
//# sourceMappingURL=EditorController.js.map