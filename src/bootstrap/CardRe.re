include Utils;


[@react.component]
let make =
    (
      ~className: option(string)=?,
      ~color: option(ColorsRe.Text.t)=?,
      ~backgroundColor: option(ColorsRe.Background.t)=?,
      ~borderColor: option(ColorsRe.Border.t)=?,
      ~children,
    ) => {
  
    let classes =
      [
        "card",
        unwrapStr(i, className),
        ColorsRe.Text.unWrap(color),
        ColorsRe.Background.unWrap(backgroundColor),
        ColorsRe.Border.unWrap(borderColor),
      ]
      |> String.concat(" ");
      <div className=classes> children </div>

  
};

module Body = {  
  [@react.component]
  let make = (~className: option(string)=?, ~children) => {

      let className =
        ["card-body", unwrapStr(i, className)] |> String.concat(" ");
      <div className> children </div>
    
  };
};

module Columns = {
  let component = ReasonReact.statelessComponent("Card.Columns");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        [unwrapStr(i, className), "card-columns"] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Deck = {
  let component = ReasonReact.statelessComponent("Card.Deck");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-deck", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Footer = {
  let component = ReasonReact.statelessComponent("Card.Footer");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-footer", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module CardGroup = {
  let component = ReasonReact.statelessComponent("Card.Group");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-group", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Header = {  
  [@react.component]
  let make = (~className: option(string)=?, ~children) => {

      let className =
        ["card-header", unwrapStr(i, className)] |> String.concat(" ");
      <div className> children </div>
    
  };
};

module Img = {
  module Fixed = {
    type t =
      | None
      | Top
      | Bottom;
    let toString = fixed =>
      "card-img"
      ++ (
        switch (fixed) {
        | None => ""
        | Top => "-top"
        | Bottom => "-bottom"
        }
      );
  };
  let component = ReasonReact.statelessComponent("Card.Img");
  let make =
      (
        ~tag: string="img",
        ~src: string="",
        ~alt: string="",
        ~fixed: Fixed.t=None,
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        [Fixed.toString(fixed), unwrapStr(i, className)]
        |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {"className": classes, "src": src, "alt": alt}
          ->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "fixed": option('fixed),
          "alt": option('alt),
          "src": option('src),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~fixed=?reactProps##fixed,
        ~alt=?reactProps##alt,
        ~src=?reactProps##src,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~src: 'src=?,
      ~alt: 'alt=?,
      ~fixed: 'fixed=?,
      ~className: 'className=?,
      unit
    ) =>
    {
      .
      "className": option('className),
      "fixed": option('fixed),
      "alt": option('alt),
      "src": option('src),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module ImgOverlay = {
  let component = ReasonReact.statelessComponent("Card.ImgOverlay");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-img-overlay", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Link = {
  let component = ReasonReact.statelessComponent("Card.Link");
  let make = (~tag: string="a", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-link", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Title = {
  let component = ReasonReact.statelessComponent("Card.Title");
  let make = (~tag: string="h4", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-title", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Subtitle = {
  let component = ReasonReact.statelessComponent("Card.SubTitle");
  let make = (~tag: string="h6", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-subtitle", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Text = {
  let component = ReasonReact.statelessComponent("Card.Text");
  let make = (~tag: string="p", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["card-text", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

/* TODO: Handle href and proper callbacks */
