/* TODO: Dropdown Size. Make the dropdown toggle when off the menu is clicked. */
include Utils;

module Color = ButtonRe.Color;

module Size = ButtonRe.Size;

type retainedProps = {isOpen: bool};

let component = ReasonReact.statelessComponent("Dropdown");

[@react.component]
let make = (~group: bool=false, ~isOpen: bool=false, ~classname: option(string)=?, ~children) => {
  let className =
    [group ? "btn-group" : "dropdown", isOpen ? "show" : "", unwrapStr(i, classname)] |> String.concat(" ");
  <div className> children </div>;
};

module Toggle = {
  /*   type retainedProps = {
         nav: bool,
         onClick: option(ReactEvent.Mouse.t => unit),
         toggle: unit => unit,
         disabled: bool,
         tag: option(string),
       }; */
  /*   let handleOnClick =
           (
             event,
             self:
               ReasonReact.self(
                 ReasonReact.stateless,
                 retainedProps,
                 ReasonReact.actionless,
               ),
           ) => {
         let props = self.retainedProps;
         props.disabled ?
           ReactEvent.Mouse.preventDefault(event) :
           {
             if (props.nav && props.tag === None) {
               ReactEvent.Mouse.preventDefault(event);
             };
             switch (props.onClick) {
             | None => ()
             | Some(cb) => cb(event)
             };
             props.toggle();
           };
       }; */

  [@react.component]
  let make =
      (
        ~caret: bool=false,
        ~disabled: bool=false,
        ~isOpen: bool,
        ~split: bool=false,
        ~color: Color.t=Color.Secondary,
        ~nav: bool=false,
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~toggle: unit => unit,
        ~classname: option(string)=?,
        ~children,
      ) => {
    let handleOnClick = event => {
      disabled
        ? ReactEvent.Mouse.preventDefault(event)
        : {
          if (nav) {
            ReactEvent.Mouse.preventDefault(event);
          };
          switch (onClick) {
          | None => ()
          | Some(cb) => cb(event)
          };
          toggle();
        };
    };
    let className =
      [
        caret || split ? "dropdown-toggle" : "",
        split ? "dropdown-toggle-split" : "",
        isOpen ? "active" : "",
        unwrapStr(i, classname),
      ]
      |> String.concat(" ");
    let tag = nav ? "a" : "button";
    switch (tag) {
    | "button" =>
      <ButtonRe color className onClick=handleOnClick disabled ariaHaspopup=true ariaExpanded=isOpen>
        children
      </ButtonRe>
    /*  React.createElementVariadic(
          ButtonRe.make,
           ButtonRe.makeProps(
            ~color,
            ~className=classNames,
            ~onClick=self.handle(handleOnClick),
            ~disabled,
            ~ariaHaspopup=true,
            ~ariaExpanded=isOpen,
            ()
          ),
          children
        ) */
    | _ => <a className href="#" onClick=handleOnClick> children </a>
    /*    ReactDOMRe.createElementVariadic(
            tag,
            ~props=
              {
                "className": classNames,
                "href": "#",
                "onClick": self.handle(handleOnClick),
              }
              ->ReactDOMRe.objToDOMProps,
            children,
          ) */
    };
  };
};

module Menu = {
  [@react.component]
  let make = (~alignRight: bool=false, ~isOpen: bool, ~classname: option(string)=?, ~children) => {
    let className =
      ["dropdown-menu", alignRight ? "dropdown-menu-right" : "", isOpen ? "show" : "", unwrapStr(i, classname)]
      |> String.concat(" ");
    <div className tabIndex=(-1) ariaHidden={!isOpen} role="menu"> children </div>;
  };
};

module Divider = {
  [@react.component]
  let make = () => {
    <div className="dropdown-divider" />;
  };
};

module Header = {
  [@react.component]
  let make = (~children) => {
    <h6 className="dropdown-header"> children </h6>;
  };
};

module Item = {
  [@react.component]
  let make =
      (
        ~disabled: bool=false,
        ~active: bool=false,
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~href: option(string)=?,
        ~className: option(string)=?,
        ~children,
      ) => {
    let handleClick = event => {
      disabled
        ? ReactEvent.Mouse.preventDefault(event)
        : (
          switch (onClick) {
          | None => ()
          | Some(cb) => cb(event)
          }
        );
    };

    let tabIndex = disabled ? (-1) : 0;

    let type_ =
      switch (onClick) {
      | Some(_) => "button"
      | None => ""
      };
    let className =
      ["dropdown-item", active ? "active" : "", disabled ? "disabled" : "", unwrapStr(i, className)]
      |> String.concat(" ");

    switch (href) {
    | None => <button className tabIndex onClick=handleClick type_> children </button>
    | Some(href) => <a className tabIndex onClick=handleClick type_ href> children </a>
    };
  };
};


/* TODO: Support Context someday */

