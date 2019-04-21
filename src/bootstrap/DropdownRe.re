/* TODO: Dropdown Size. Make the dropdown toggle when off the menu is clicked. */
include Utils;

module Color = ButtonRe.Color;

module Size = ButtonRe.Size;

type retainedProps = {isOpen: bool};

let component = ReasonReact.statelessComponent("Dropdown");

let make =
    (
      ~tag: string="div",
      ~group: bool=false,
      ~isOpen: bool=false,
      ~classname: option(string)=?,
      children,
    ) => {
  ...component,
  render: _self => {
    let classNames =
      [
        group ? "btn-group" : "dropdown",
        isOpen ? "show" : "",
        unwrapStr(i, classname),
      ]
      |> String.concat(" ");
    ReactDOMRe.createElementVariadic(
      tag,
      ~props={"className": classNames}->ReactDOMRe.objToDOMProps,
      children,
    );
  },
};

module Toggle = {
  type retainedProps = {
    nav: bool,
    onClick: option(ReactEvent.Mouse.t => unit),
    toggle: unit => unit,
    disabled: bool,
    tag: option(string),
  };
  let handleOnClick =
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
  };
  let component =
    ReasonReact.statelessComponentWithRetainedProps("Dropdown.Toggle");
  let make =
      (
        ~tag: option(string)=?,
        ~caret: bool=false,
        ~disabled: bool=false,
        ~isOpen: bool,
        ~split: bool=false,
        ~color: Color.t=Color.Secondary,
        ~nav: bool=false,
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~toggle: unit => unit,
        ~classname: option(string)=?,
        children,
      ) => {
    ...component,
    retainedProps: {
      onClick,
      disabled,
      tag,
      nav,
      toggle,
    },
    render:
      (
        self:
          ReasonReact.self(
            ReasonReact.stateless,
            retainedProps,
            ReasonReact.actionless,
          ),
      ) => {
      let classNames =
        [
          caret || split ? "dropdown-toggle" : "",
          split ? "dropdown-toggle-split" : "",
          isOpen ? "active" : "",
          unwrapStr(i, classname),
        ]
        |> String.concat(" ");
      let tag =
        switch (tag, nav) {
        | (None, true) => "a"
        | (None, false) => "button"
        | (Some(t), _) => t
        };
      switch (tag) {
      | "button" => React.null//<ButtonRe color className=classNames onClick=self.handle(handleOnClick) disabled ariaHaspopup=true ariaExpanded=isOpen> (React.string("hey")) </ButtonRe>
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
      | _ =>
        ReactDOMRe.createElementVariadic(
          tag,
          ~props=
            {
              "className": classNames,
              "href": "#",
              "onClick": self.handle(handleOnClick),
            }
            ->ReactDOMRe.objToDOMProps,
          children,
        )
      };
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
          "classname": option('classname),
          "toggle": 'toggle,
          "onClick": option('onClick),
          "nav": option('nav),
          "color": option('color),
          "split": option('split),
          "isOpen": 'isOpen,
          "disabled": option('disabled),
          "caret": option('caret),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~classname=?reactProps##classname,
        ~toggle=reactProps##toggle,
        ~onClick=?reactProps##onClick,
        ~nav=?reactProps##nav,
        ~color=?reactProps##color,
        ~split=?reactProps##split,
        ~isOpen=reactProps##isOpen,
        ~disabled=?reactProps##disabled,
        ~caret=?reactProps##caret,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~caret: 'caret=?,
      ~disabled: 'disabled=?,
      ~isOpen: 'isOpen,
      ~split: 'split=?,
      ~color: 'color=?,
      ~nav: 'nav=?,
      ~onClick: 'onClick=?,
      ~toggle: 'toggle,
      ~classname: 'classname=?,
      unit
    ) =>
    {
      .
      "classname": option('classname),
      "toggle": 'toggle,
      "onClick": option('onClick),
      "nav": option('nav),
      "color": option('color),
      "split": option('split),
      "isOpen": 'isOpen,
      "disabled": option('disabled),
      "caret": option('caret),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Menu = {
  let component = ReasonReact.statelessComponent("Dropdown.Menu");
  let make =
      (
        ~tag: string="div",
        ~alignRight: bool=false,
        ~isOpen: bool,
        ~classname: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let classNames =
        [
          "dropdown-menu",
          alignRight ? "dropdown-menu-right" : "",
          isOpen ? "show" : "",
          unwrapStr(i, classname),
        ]
        |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {
            "className": classNames,
            "tabIndex": "-1",
            "aria-hidden": !isOpen,
            "role": "menu",
          }
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
          "classname": option('classname),
          "isOpen": 'isOpen,
          "alignRight": option('alignRight),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~classname=?reactProps##classname,
        ~isOpen=reactProps##isOpen,
        ~alignRight=?reactProps##alignRight,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~alignRight: 'alignRight=?,
      ~isOpen: 'isOpen,
      ~classname: 'classname=?,
      unit
    ) =>
    {
      .
      "classname": option('classname),
      "isOpen": 'isOpen,
      "alignRight": option('alignRight),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Divider = {
  let component = ReasonReact.statelessComponent("Dropdown.Divider");
  let make = children => {
    ...component,
    render: _self =>
      ReactDOMRe.createElementVariadic(
        "div",
        ~props={"className": "dropdown-divider"}->ReactDOMRe.objToDOMProps,
        children,
      ),
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component, (reactProps: {. "children": 'children}) =>
      make(reactProps##children)
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, unit) => {. "children": 'children} =
    "";
};

module Header = {
  let component = ReasonReact.statelessComponent("Dropdown.Header");
  let make = children => {
    ...component,
    render: _self =>
      ReactDOMRe.createElementVariadic(
        "h6",
        ~props={"className": "dropdown-header"}->ReactDOMRe.objToDOMProps,
        children,
      ),
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component, (reactProps: {. "children": 'children}) =>
      make(reactProps##children)
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, unit) => {. "children": 'children} =
    "";
};

module Item = {
  let component = ReasonReact.statelessComponent("Dropdown.Item");
  let make =
      (
        ~disabled: bool=false,
        ~active: bool=false,
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~href: option(string)=?,
        ~classname: option(string)=?,
        children,
      ) => {
    ...component,
    render: self => {
      let click = (event, _self) =>
        disabled ?
          ReactEvent.Mouse.preventDefault(event) :
          (
            switch (onClick) {
            | None => ()
            | Some(cb) => cb(event)
            }
          );
      let tabIndex = disabled ? "-1" : "0";
      let tag =
        switch (href) {
        | None => "button"
        | Some(_) => "a"
        };
      let type_ =
        switch (onClick, tag) {
        | (Some(_), "button") => Some("button")
        | (_, _) => None
        };
      let classes =
        [
          "dropdown-item",
          active ? "active" : "",
          disabled ? "disabled" : "",
          unwrapStr(i, classname),
        ]
        |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {
            "className": classes,
            "tabIndex": tabIndex,
            "onClick": self.handle(click),
            "type": Js.Nullable.fromOption(type_),
            "href": Js.Nullable.fromOption(href),
          }
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
          "classname": option('classname),
          "href": option('href),
          "onClick": option('onClick),
          "active": option('active),
          "disabled": option('disabled),
          "children": 'children,
        },
      ) =>
      make(
        ~classname=?reactProps##classname,
        ~href=?reactProps##href,
        ~onClick=?reactProps##onClick,
        ~active=?reactProps##active,
        ~disabled=?reactProps##disabled,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~disabled: 'disabled=?,
      ~active: 'active=?,
      ~onClick: 'onClick=?,
      ~href: 'href=?,
      ~classname: 'classname=?,
      unit
    ) =>
    {
      .
      "classname": option('classname),
      "href": option('href),
      "onClick": option('onClick),
      "active": option('active),
      "disabled": option('disabled),
      "children": 'children,
    } =
    "";
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
        "classname": option('classname),
        "isOpen": option('isOpen),
        "group": option('group),
        "tag": option('tag),
        "children": 'children,
      },
    ) =>
    make(
      ~classname=?reactProps##classname,
      ~isOpen=?reactProps##isOpen,
      ~group=?reactProps##group,
      ~tag=?reactProps##tag,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~tag: 'tag=?,
    ~group: 'group=?,
    ~isOpen: 'isOpen=?,
    ~classname: 'classname=?,
    unit
  ) =>
  {
    .
    "classname": option('classname),
    "isOpen": option('isOpen),
    "group": option('group),
    "tag": option('tag),
    "children": 'children,
  } =
  "";

/*  ~disabled: bool=false, */

/* ~toggle: option(unit => unit)=?, */

/* ~right: bool=false, */

/* TODO: Support Context someday */

/* ~toggle: bool=true, */
