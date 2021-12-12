"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.RectangleRenderer = void 0;
var ShapeRenderer_1 = require("./ShapeRenderer");
var RectangleRenderer = /** @class */ (function (_super) {
    __extends(RectangleRenderer, _super);
    function RectangleRenderer(model, canvas) {
        return _super.call(this, model, canvas) || this;
    }
    RectangleRenderer.prototype.getShapeHtmlImpl = function () {
        var model = this.model;
        var width = model.width;
        var height = model.height;
        return "<svg\n            xmlns='http://www.w3.org/2000/svg'\n            width='".concat(width, "'\n            height='").concat(height, "'\n            viewPort='0 0 ").concat(width, " ").concat(height, "'>\"\n            <polygon points='").concat(0, ",").concat(0, " ").concat(width, ",").concat(0, " ").concat(width, ",").concat(height, " ").concat(0, ",").concat(height, "' fill='black' />\n        </svg>");
    };
    return RectangleRenderer;
}(ShapeRenderer_1.ShapeRenderer));
exports.RectangleRenderer = RectangleRenderer;
//# sourceMappingURL=Rectangle.js.map