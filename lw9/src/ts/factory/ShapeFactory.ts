import {ShapeType} from "../common/ShapeType";
import {Shape} from "../model/Shape";
import {RectangleRenderer} from "../view/Rectangle";
import {EllipseRenderer} from "../view/Ellipse";
import {TriangleRenderer} from "../view/Triangle";
import {CanvasModel} from "../model/CanvasModel";
import {CanvasRenderer} from "../view/CanvasRenderer";

const DEFAULT_WIDTH = 100
const DEFAULT_HEIGHT = 70

type ShapeModelType = {
    shapeType: ShapeType,
    canvas: CanvasModel,
    width?: number,
    height?: number,
    left?: number,
    top?: number,
}

class ShapeFactory {
    static createShapeModel({
        shapeType,
        canvas,
        width = DEFAULT_WIDTH,
        height = DEFAULT_HEIGHT,
        left = canvas.getWidth() / 2 - DEFAULT_HEIGHT / 2,
        top = canvas.getHeight() / 2 - DEFAULT_HEIGHT / 2,
    }: ShapeModelType) {
        return new Shape(
            canvas,
            width,
            height,
            top,
            left,
            shapeType,
        )
    }

    static createShapeRenderer(model: Shape) {
        switch (model.shapeType) {
            case "rectangle":
                return new RectangleRenderer(model)
            case "ellipse":
                return new EllipseRenderer(model)
            case "triangle":
                return new TriangleRenderer(model)
        }
    }
}

export {
    ShapeFactory,
}