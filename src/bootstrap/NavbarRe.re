include Utils;

module Fixed = {
  type t =
    | Top
    | Bottom;
  let toString = fixed =>
    switch (fixed) {
    | Top => "top"
    | Bottom => "bottom"
    };
};

let component = ReasonReact.statelessComponent("NavBar");

let make =
    (
      ~light: bool=false,
      ~fixed: option(Fixed.t)=?,
      ~sticky: option(string)=?,
      ~color: option(ColorsRe.Background.t)=?,
      ~role: option(string)=?,
      ~tag: string="nav",
      ~className: option(string)=?,
      ~toggleable: bool=false,
      children,
    ) => {
  ...component,
  render: _self => {
    let fixedClass = (cls: option(Fixed.t)) =>
      switch (cls) {
      | None => ""
      | Some(x) => "fixed-" ++ Fixed.toString(x)
      };
    let stickyClass = (cls: option(string)) =>
      switch (cls) {
      | None => ""
      | Some(x) => "sticky-" ++ x
      };
    let classes =
      [
        "navbar",
        toggleable ? "navbar-toggleable" : "",
        light ? "navbar-light" : "navbar-dark",
        unwrapStr(ColorsRe.Background.toString, color),
        fixedClass(fixed),
        stickyClass(sticky),
        unwrapStr(i, className),
      ]
      |> String.concat(" ");
    ReactDOMRe.createElementVariadic(
      tag,
      ~props={"className": classes, "role": role}->ReactDOMRe.objToDOMProps,
      children,
    );
  },
};

module Brand = {
  let component = ReasonReact.statelessComponent("Navbar.Brand");
  let make =
      (
        ~tag: string="a",
        ~className: option(string)=?,
        ~href: string="",
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["navbar-brand", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes, "href": href}->ReactDOMRe.objToDOMProps,
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
          "href": option('href),
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~href=?reactProps##href,
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~className: 'className=?,
      ~href: 'href=?,
      unit
    ) =>
    {
      .
      "href": option('href),
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Toggler = {
  [@react.component]
  let make = (~tag:string="button", ~type_:string="button", ~onClick: option(ReactEvent.Mouse.t => unit),
        ~className: string=""
        ) => {
          let span = <span className="navbar-toggler-icon" />;
          let classes =
        ["navbar-toggler", className] |> String.concat(" ");
    ReactDOMRe.createElementVariadic(tag, ~props=
          {
            "type": type_,
            "className": classes,
            "onClick": onClick,
          }
          ->ReactDOMRe.objToDOMProps, [|span|])
  };
/*   let component = ReasonReact.statelessComponent("Navbar.Toggler");
  let make =
      (
        ~tag: string="button",
        ~type_: string="button",
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~className: option(string)=?,
        _children,
      ) => {
    ...component,
    render: _self => {
      let span = <span className="navbar-toggler-icon" />;
      let classes =
        ["navbar-toggler", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {
            "type": type_,
            "className": classes,
            "onClick": Js.Nullable.fromOption(onClick),
          }
          ->ReactDOMRe.objToDOMProps,
        [|span|],
      );
    }
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
          "onClick": option('onClick),
          "type_": option('type_),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~onClick=?reactProps##onClick,
        ~type_=?reactProps##type_,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~type_: 'type_=?,
      ~onClick: 'onClick=?,
      ~className: 'className=?,
      unit
    ) =>
    {
      .
      "className": option('className),
      "onClick": option('onClick),
      "type_": option('type_),
      "tag": option('tag),
      "children": 'children,
    } =
    ""; */
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
        "toggleable": option('toggleable),
        "className": option('className),
        "tag": option('tag),
        "role": option('role),
        "color": option('color),
        "sticky": option('sticky),
        "fixed": option('fixed),
        "light": option('light),
        "children": 'children,
      },
    ) =>
    make(
      ~toggleable=?reactProps##toggleable,
      ~className=?reactProps##className,
      ~tag=?reactProps##tag,
      ~role=?reactProps##role,
      ~color=?reactProps##color,
      ~sticky=?reactProps##sticky,
      ~fixed=?reactProps##fixed,
      ~light=?reactProps##light,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~light: 'light=?,
    ~fixed: 'fixed=?,
    ~sticky: 'sticky=?,
    ~color: 'color=?,
    ~role: 'role=?,
    ~tag: 'tag=?,
    ~className: 'className=?,
    ~toggleable: 'toggleable=?,
    unit
  ) =>
  {
    .
    "toggleable": option('toggleable),
    "className": option('className),
    "tag": option('tag),
    "role": option('role),
    "color": option('color),
    "sticky": option('sticky),
    "fixed": option('fixed),
    "light": option('light),
    "children": 'children,
  } =
  "";

/* cssModule::(cssModule: option (Js.t {..}))=? */

/* cssModule::(cssModule: option (Js.t {..}))=? */
