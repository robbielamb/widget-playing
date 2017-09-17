

module TextColor = {
    type t =
      | White
      | Dark
      | Muted
      | Hide
      | Primary
      | Secondary
      | Success
      | Info
      | Warning
      | Danger;
    let toString color =>
      "text-"^switch color {
      | White => "white"
      | Dark => "dark"
      | Muted => "muted"
      | Hide => "hide"
      | Primary => "primary"
      | Secondary => "secondary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      };
    let unWrap = Utils.unwrapStr toString;
  };
  
  module BackgroundColor = {
    type t =
      | Primary
      | Secondary
      | Success
      | Info
      | Warning
      | Danger
      | Light
      | Dark
      | White
      | Transparent;
    let toString color =>
      "bg-" ^ (
        switch color {
        | Primary => "primary"
        | Secondary => "secondary"
        | Success => "success"
        | Info => "info"
        | Warning => "warning"
        | Danger => "danger"
        | Dark => "dark"
        | Light => "light"
        | White => "white"
        | Transparent => "transparent"
        }
      );
    let unWrap = Utils.unwrapStr toString;
  };
  
  module BorderColor = {
    type t =
      | Primary
      | Secondary
      | Success
      | Info
      | Warning
      | Danger
      | Light
      | Dark
      | White
      | Transparent;
    let toString color =>
      "border-" ^ (
        switch color {
        | Primary => "primary"
        | Secondary => "secondary"
        | Success => "success"
        | Info => "info"
        | Warning => "warning"
        | Danger => "danger"
        | Dark => "dark"
        | Light => "light"
        | White => "white"
        | Transparent => "transparent"
        }
      );
    let unWrap = Utils.unwrapStr toString;
  };