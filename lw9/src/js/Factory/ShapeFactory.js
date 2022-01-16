"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeFactory = void 0;
var Shape_1 = require("../model/Shape");
var Rectangle_1 = require("../view/Rectangle");
var Ellipse_1 = require("../view/Ellipse");
var Triangle_1 = require("../view/Triangle");
var DEFAULT_WIDTH = 100;
var DEFAULT_HEIGHT = 70;
var ShapeFactory = /** @class */ (function () {
    function ShapeFactory() {
    }
    ShapeFactory.createShapeModel = function (_a) {
        var shapeType = _a.shapeType, canvas = _a.canvas, _b = _a.width, width = _b === void 0 ? DEFAULT_WIDTH : _b, _c = _a.height, height = _c === void 0 ? DEFAULT_HEIGHT : _c, _d = _a.left, left = _d === void 0 ? canvas.getWidth() / 2 - DEFAULT_HEIGHT / 2 : _d, _e = _a.top, top = _e === void 0 ? canvas.getHeight() / 2 - DEFAULT_HEIGHT / 2 : _e;
        return new Shape_1.Shape(width, height, top, left, shapeType);
    };
    ShapeFactory.createShapeRenderer = function (model, canvas) {
        switch (model.shapeType) {
            case "rectangle":
                return new Rectangle_1.RectangleRenderer(model, canvas);
            case "ellipse":
                return new Ellipse_1.EllipseRenderer(model, canvas);
            case "triangle":
                return new Triangle_1.TriangleRenderer(model, canvas);
        }
    };
    return ShapeFactory;
}());
exports.ShapeFactory = ShapeFactory;
//# sourceMappingURL=ShapeFactory.js.map