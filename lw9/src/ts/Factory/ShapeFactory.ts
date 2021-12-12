import {ShapeType} from "../ShapeType";
import {Canvas} from "../Canvas/Canvas";
import {Shape} from "../shapes/Shape";
import {RectangleRenderer} from "../shapes/Rectangle";
import {EllipseRenderer} from "../shapes/Ellipse";
import {TriangleRenderer} from "../shapes/Triangle";

const DEFAULT_WIDTH = 100
const DEFAULT_HEIGHT = 70

class ShapeFactory {
    static createShapeModel(shapeType: ShapeType, canvas: Canvas) {
        const canvasWidth = canvas.getWidth()
        const canvasHeight = canvas.getHeight()
        return new Shape(
            DEFAULT_WIDTH,
            DEFAULT_HEIGHT,
            canvasHeight / 2 - DEFAULT_HEIGHT / 2,
            canvasWidth / 2 - DEFAULT_WIDTH / 2,
            shapeType,
        )
    }

    static createShapeRenderer(model: Shape, canvas: Canvas) {
        switch (model.shapeType) {
            case "rectangle":
                return new RectangleRenderer(model, canvas)
            case "ellipse":
                return new EllipseRenderer(model, canvas)
            case "triangle":
                return new TriangleRenderer(model, canvas)
        }
    }
}

export {
    ShapeFactory,
}