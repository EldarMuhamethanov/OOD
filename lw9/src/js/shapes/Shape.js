"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Shape = void 0;
var Signal_1 = require("../Signal");
var generateUid_1 = require("../common/generateUid");
var Shape = /** @class */ (function () {
    function Shape(width, height, top, left, shapeType) {
        this.onRectChange = new Signal_1.Signal();
        this.onSelectedChange = new Signal_1.Signal();
        this.m_width = width;
        this.m_height = height;
        this.m_left = left;
        this.m_top = top;
        this.m_shapeType = shapeType;
        this.m_id = (0, generateUid_1.generateUid)();
        this.m_isSelected = false;
    }
    Shape.prototype.getOnRectChange = function () {
        return this.onRectChange;
    };
    Shape.prototype.getOnSelectedChange = function () {
        return this.onSelectedChange;
    };
    Object.defineProperty(Shape.prototype, "id", {
        get: function () {
            return this.m_id;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "shapeType", {
        get: function () {
            return this.m_shapeType;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "width", {
        get: function () {
            return this.m_width;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "height", {
        get: function () {
            return this.m_height;
        },
        enumerable: false,
        configurable: true
    });
    Shape.prototype.setRect = function (left, top, width, height) {
        this.m_top = top;
        this.m_left = left;
        this.m_width = width;
        this.m_height = height;
        this.onRectChange.dispatch();
    };
    Shape.prototype.setSelected = function (selected) {
        this.m_isSelected = selected;
        this.onSelectedChange.dispatch();
    };
    Object.defineProperty(Shape.prototype, "isSelected", {
        get: function () {
            return this.m_isSelected;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "left", {
        get: function () {
            return this.m_left;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "top", {
        get: function () {
            return this.m_top;
        },
        enumerable: false,
        configurable: true
    });
    return Shape;
}());
exports.Shape = Shape;
//# sourceMappingURL=Shape.js.map