"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeFactory = void 0;
var Shape_1 = require("../shapes/Shape");
var Rectangle_1 = require("../shapes/Rectangle");
var Ellipse_1 = require("../shapes/Ellipse");
var Triangle_1 = require("../shapes/Triangle");
var DEFAULT_WIDTH = 100;
var DEFAULT_HEIGHT = 70;
var ShapeFactory = /** @class */ (function () {
    function ShapeFactory() {
    }
    ShapeFactory.createShapeModel = function (shapeType, canvas) {
        var canvasWidth = canvas.getWidth();
        var canvasHeight = canvas.getHeight();
        return new Shape_1.Shape(DEFAULT_WIDTH, DEFAULT_HEIGHT, canvasHeight / 2 - DEFAULT_HEIGHT / 2, canvasWidth / 2 - DEFAULT_WIDTH / 2, shapeType);
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