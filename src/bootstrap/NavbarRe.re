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

[@react.component]
let make =
    (
      ~light: bool=false,
      ~fixed: option(Fixed.t)=?,
      ~sticky: option(string)=?,
      ~color: option(ColorsRe.Background.t)=?,
      ~role: option(string)=?,
      ~className: option(string)=?,
      ~toggleable: bool=false,
      ~children,
    ) => {
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
    let className =
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
      <nav className ?role> children </nav>   
  
};

module Brand = {  
  [@react.component]
  let make =
      (
        ~className: option(string)=?,
        ~href: string="",
        ~children,
      ) => {
  
      let className =
        ["navbar-brand", unwrapStr(i, className)] |> String.concat(" ");
        <a className href> children </a>
     
    
  };
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

/* cssModule::(cssModule: option (Js.t {..}))=? */

/* cssModule::(cssModule: option (Js.t {..}))=? */
