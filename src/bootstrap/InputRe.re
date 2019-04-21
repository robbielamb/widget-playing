include Utils;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString = size =>
    switch (size) {
    | None => ""
    | Large => "form-control-lg"
    | Small => "form-control-sm"
    };
};

type inputType =
  | Button
  | Checkbox
  | Date
  | Email
  | File
  | Password
  | Radio
  | Reset
  | Select
  | Submit
  | Text
  | TextArea
  | Url;

let component = ReasonReact.statelessComponent("Input");

let make =
    (
      ~tag: string="input",
      ~id: option(string)=?,
      ~name: string="",
      ~type_: inputType=Text,
      ~size: Size.t=Size.None,
      ~plainText: bool=false,
      ~placeholder: option(string)=?,
      ~disabled: bool=false,
      ~multiple: option(bool)=?,
      ~className: option(string)=?,
      ~onInput: option(ReactEvent.Keyboard.t => unit)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onBlur: option(ReactEvent.Focus.t => unit)=?,
      ~checked: option(bool)=?,
      ~valid: option(bool)=?,
      ~value: option(string)=?,
      ~required: bool=false,
      children,
    ) => {
  ...component,
  render: _self => {
    let checkInput =
      switch (type_) {
      | Radio => true
      | Checkbox => true
      | _ => false
      };
    let fileInput = type_ === File;
    let tag =
      switch (type_) {
      | TextArea => "textarea"
      | Select => "select"
      | _ => tag
      };
    let typeAttribute =
      switch (type_) {
      | Button => "button"
      | Checkbox => "checkbox"
      | Date => "date"
      | Email => "email"
      | File => "file"
      | Password => "password"
      | Radio => "radio"
      | Reset => "reset"
      | Select => ""
      | Submit => "submit"
      | TextArea => ""
      | Text => "text"
      | Url => "url"
      };
    let formControlClass =
      switch (plainText, fileInput, checkInput) {
      | (true, false, false) => "form-control-planetext"
      | (false, true, false) => "form-control-file"
      | (false, false, true) => "form-check-input"
      | (_, _, _) => "form-control"
      };
    let validClassName =
      switch (valid) {
      | None => ""
      | Some(true) => "is-valid"
      | Some(false) => "is-invalid"
      };
    let className =
      [
        unwrapStr(i, className),
        Size.toString(size),
        formControlClass,
        validClassName,
      ]
      |> String.concat(" ");
    let props =
      {
        "className": className,
        "id": Js.Nullable.fromOption(id),
        "name": name,
        "type": typeAttribute,
        "placeholder": Js.Nullable.fromOption(placeholder),
        "multiple": Js.Nullable.fromOption(multiple),
        "disabled": disabled,
        "onInput": Js.Nullable.fromOption(onInput),
        "onChange": Js.Nullable.fromOption(onChange),
        "onBlur": Js.Nullable.fromOption(onBlur),
        "checked": Js.Nullable.fromOption(checked),
        "value": Js.Nullable.fromOption(value),
        "required": required,
      }
      ->ReactDOMRe.objToDOMProps;
    ReactDOMRe.createElementVariadic(tag, ~props, children);
  },
};

module Label = {
  include LayoutRe.ColSizes;
  module Size = {
    type t =
      | SM
      | LG;
    let toString = size =>
      switch (size) {
      | SM => "sm"
      | LG => "lg"
      };
  };
  let component = ReasonReact.statelessComponent("Form.Label");
  let make =
      (
        ~id: option(string)=?,
        ~tag: string="label",
        ~for_: option(string)=?,
        ~hidden: bool=false,
        ~check: bool=false,
        ~inline: bool=false,
        ~disabled: bool=false,
        ~size: option(Size.t)=?,
        ~color: option(ColorsRe.Text.t)=?,
        ~xs: option(shape)=Some(shape()),
        ~sm: option(shape)=?,
        ~md: option(shape)=?,
        ~lg: option(shape)=?,
        ~xl: option(shape)=?,
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let colClasses = processShapeList(xs, sm, md, lg, xl);
      let containsColClasses = Belt.List.length(colClasses) > 0;
      let classes =
        [
          unwrapStr(i, className),
          hidden ? "sr-only" : "",
          check && !inline ? "form-check-label" : "",
          check && inline ? "form-check-inline" : "",
          check && inline && disabled ? "disabled" : "",
          switch (size) {
          | None => ""
          | Some(s) => "col-form-label-" ++ Size.toString(s)
          },
          containsColClasses ? "col-form-label" : "",
          !check && !containsColClasses ? "form-control-label" : "",
          ColorsRe.Text.unWrap(color),
        ]
        ->(Belt.List.concat(colClasses))
        |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {
            "className": classes,
            "id": Js.Nullable.fromOption(id),
            "htmlFor": Js.Nullable.fromOption(for_),
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
          "className": option('className),
          "xl": option('xl),
          "lg": option('lg),
          "md": option('md),
          "sm": option('sm),
          "xs": option('xs),
          "color": option('color),
          "size": option('size),
          "disabled": option('disabled),
          "inline": option('inline),
          "check": option('check),
          "hidden": option('hidden),
          "for_": option('for_),
          "tag": option('tag),
          "id": option('id),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~xl=?reactProps##xl,
        ~lg=?reactProps##lg,
        ~md=?reactProps##md,
        ~sm=?reactProps##sm,
        ~xs=?reactProps##xs,
        ~color=?reactProps##color,
        ~size=?reactProps##size,
        ~disabled=?reactProps##disabled,
        ~inline=?reactProps##inline,
        ~check=?reactProps##check,
        ~hidden=?reactProps##hidden,
        ~for_=?reactProps##for_,
        ~tag=?reactProps##tag,
        ~id=?reactProps##id,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~id: 'id=?,
      ~tag: 'tag=?,
      ~for_: 'for_=?,
      ~hidden: 'hidden=?,
      ~check: 'check=?,
      ~inline: 'inline=?,
      ~disabled: 'disabled=?,
      ~size: 'size=?,
      ~color: 'color=?,
      ~xs: 'xs=?,
      ~sm: 'sm=?,
      ~md: 'md=?,
      ~lg: 'lg=?,
      ~xl: 'xl=?,
      ~className: 'className=?,
      unit
    ) =>
    {
      .
      "className": option('className),
      "xl": option('xl),
      "lg": option('lg),
      "md": option('md),
      "sm": option('sm),
      "xs": option('xs),
      "color": option('color),
      "size": option('size),
      "disabled": option('disabled),
      "inline": option('inline),
      "check": option('check),
      "hidden": option('hidden),
      "for_": option('for_),
      "tag": option('tag),
      "id": option('id),
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
        "required": option('required),
        "value": option('value),
        "valid": option('valid),
        "checked": option('checked),
        "onBlur": option('onBlur),
        "onChange": option('onChange),
        "onInput": option('onInput),
        "className": option('className),
        "multiple": option('multiple),
        "disabled": option('disabled),
        "placeholder": option('placeholder),
        "plainText": option('plainText),
        "size": option('size),
        "type_": option('type_),
        "name": option('name),
        "id": option('id),
        "tag": option('tag),
        "children": 'children,
      },
    ) =>
    make(
      ~required=?reactProps##required,
      ~value=?reactProps##value,
      ~valid=?reactProps##valid,
      ~checked=?reactProps##checked,
      ~onBlur=?reactProps##onBlur,
      ~onChange=?reactProps##onChange,
      ~onInput=?reactProps##onInput,
      ~className=?reactProps##className,
      ~multiple=?reactProps##multiple,
      ~disabled=?reactProps##disabled,
      ~placeholder=?reactProps##placeholder,
      ~plainText=?reactProps##plainText,
      ~size=?reactProps##size,
      ~type_=?reactProps##type_,
      ~name=?reactProps##name,
      ~id=?reactProps##id,
      ~tag=?reactProps##tag,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~tag: 'tag=?,
    ~id: 'id=?,
    ~name: 'name=?,
    ~type_: 'type_=?,
    ~size: 'size=?,
    ~plainText: 'plainText=?,
    ~placeholder: 'placeholder=?,
    ~disabled: 'disabled=?,
    ~multiple: 'multiple=?,
    ~className: 'className=?,
    ~onInput: 'onInput=?,
    ~onChange: 'onChange=?,
    ~onBlur: 'onBlur=?,
    ~checked: 'checked=?,
    ~valid: 'valid=?,
    ~value: 'value=?,
    ~required: 'required=?,
    unit
  ) =>
  {
    .
    "required": option('required),
    "value": option('value),
    "valid": option('valid),
    "checked": option('checked),
    "onBlur": option('onBlur),
    "onChange": option('onChange),
    "onInput": option('onInput),
    "className": option('className),
    "multiple": option('multiple),
    "disabled": option('disabled),
    "placeholder": option('placeholder),
    "plainText": option('plainText),
    "size": option('size),
    "type_": option('type_),
    "name": option('name),
    "id": option('id),
    "tag": option('tag),
    "children": 'children,
  } =
  "";
