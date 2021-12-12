"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeController = void 0;
var ShapeController = /** @class */ (function () {
    function ShapeController(model, view) {
        this.m_model = model;
        this.m_view = view;
    }
    ShapeController.prototype.setRect = function (left, top, width, height) {
        this.m_model.setRect(left, top, width, height);
    };
    ShapeController.prototype.setPosition = function (left, top) {
        this.m_model.setRect(left, top, this.m_model.width, this.m_model.height);
    };
    ShapeController.prototype.setSize = function (width, height) {
        this.m_model.setRect(this.m_model.left, this.m_model.top, width, height);
    };
    ShapeController.prototype.setIsSelected = function (isSelected) {
        this.m_model.setSelected(isSelected);
    };
    return ShapeController;
}());
exports.ShapeController = ShapeController;
//# sourceMappingURL=ShapeController.js.map